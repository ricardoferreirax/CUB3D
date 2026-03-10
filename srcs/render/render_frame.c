/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/10 23:34:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	clear_sprite_z(t_game *g)
{
	int	i;
	int	n;

	if (!g || !g->ray.sprite_z)
		return ;
	n = g->win.width * g->win.height;
	i = 0;
	while (i < n)
	{
		g->ray.sprite_z[i] = 1e30;
		i++;
	}
}

void	render_base_into_buffer(t_game *s)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < s->base.height)
	{
		x = 0;
		while (x < s->base.width)
		{
			color = pixel_get(&s->base, x, y);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&s->win.frame_buffer, x + s->win.width / 2, y
					+ s->win.height / 2, color);
			x++;
		}
		y++;
	}
}

void	render_sprite_into_framebuffer(t_game *game, t_point coord,
		t_sprite_ref *sprite)
{
	t_point			point;
	unsigned int	color;

	point.y = 0;
	while (point.y < sprite->height)
	{
		point.x = 0;
		while (point.x < sprite->width)
		{
			color = pixel_get(&game->sprite_sheet.sprite_img, point.x
					+ sprite->coord.x, point.y + sprite->coord.y);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&game->win.frame_buffer, point.x + coord.x, point.y
					+ coord.y, color);
			point.x++;
		}
		point.y++;
	}
}

t_point	continue_travel(t_ghost ghost, int invalid_dir)
{
	int	dir;

	dir = (invalid_dir + 2) % 4;
	int direction[4][2] = {
		{0, -1}, // up
		{-1, 0}, // left
		{0, 1},  // down
		{1, 0}   // right
	};
	return ((t_point){.x = ghost.pos.pixel_pos.x + direction[dir][0], .y = ghost.pos.pixel_pos.y
		+ direction[dir][1]});
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

void	ghost_move_pixel(t_ghost *gh, int dx, int dy)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x += dx; // adiciona o deslocamento x (pixels) à posição atual do ghost
	gh->pos.pixel_pos.y += dy; // adiciona o deslocamento y (pixels) à posição atual do ghost
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE; // converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE; // converte a posição y do ghost de pixels para tiles
}

int	ghost_in_penhouse(t_ghost *ghost, char **map)
{
	t_point	gate;
	int		x;
	int		y;

	if (!ghost || !map)
		return (0);
	gate = find_c(map, GATE); // procura a posição do gate no mapa
	if (gate.x < 0 || gate.y < 0) // verifica se o gate foi encontrado
		return (0);
	x = ghost->pos.pixel_pos.x / TILE_SIZE; // converte a posição x do ghost de pixeis para de tiles
	y = ghost->pos.pixel_pos.y / TILE_SIZE; // converte a posição y do ghost de pixeis para de tiles
	if (x < gate.x - 2 || x > gate.x + 3) // verifica se o ghost está fora da largura da penhouse 
		return (0);
	if (y < gate.y) // verifica se o ghost já passou em cima do gate
		return (0); // se passou, então saiu da penhouse
	return (1); // está dentro da penhouse
}

static t_point	find_gate_exit(char **map)
{
	t_point	gate; // guarda aposição do gate no mapa

	gate = find_c(map, GATE); // procura a posição do gate no mapa
	if (gate.x >= 0 && gate.y >= 0) // verifica se o gate foi encontrado
	{
		gate.x += 1; // move um tile para a direita do gate para encontrar o centro da porta
		gate.y -= 1; // move um tile para cima do gate para encontrar a posição de saída da penhouse
	}
	return (gate); // devolve o tile da saída da penhouse
}

int	chose_next_move(t_ghost *ghost, char **map)
{
	int		i;
	int		best;
	int		best_dir;
	int		dist;
	t_point	target;
	int		direction[4][2] = {
		{-1, 0}, // para cima
		{0, -1}, // para a esquerda
		{1, 0}, // para baixo
		{0, 1} // para a direita
	};

	i = 0;
	best = -1;
	best_dir = -1;
	if (!ghost || !map)
		return (-1);
	if (ghost_in_penhouse(ghost, map)) // se o ghost estiver na penhouse 
		target = find_gate_exit(map); // o target passa a ser a saída da penhouse
	else
		target = ghost->target_tile; // caso contrário, o target é o tile 'b', 'p', 'i' ou 'c'
	while (i < 4)
	{
		if (map[ghost->pos.pixel_pos.y / TILE_SIZE + direction[i][0]]
			[ghost->pos.pixel_pos.x / TILE_SIZE + direction[i][1]] != WALL
			&& i != ghost->invalid_dir)
		{
			dist = (((ghost->pos.pixel_pos.x / TILE_SIZE) + direction[i][1])
					- target.x) * ((((ghost->pos.pixel_pos.x / TILE_SIZE)
							+ direction[i][1]) - target.x))
				+ ((((ghost->pos.pixel_pos.y / TILE_SIZE) + direction[i][0])
						- target.y) * ((((ghost->pos.pixel_pos.y / TILE_SIZE)
								+ direction[i][0]) - target.y)));
			if (best == -1 || dist < best)
			{
				best = dist;
				best_dir = i;
			}
		}
		i++;
	}
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	ghost_move_pixel(ghost, direction[best_dir][1], direction[best_dir][0]); // move o ghost um pixel na direção escolhida
	return ((best_dir + 2) % 4);
}

void	ghost_set_pixel_pos(t_ghost *gh, int px, int py)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x = px; // define a posição x do ghost em pixels
	gh->pos.pixel_pos.y = py; // define a posição y do ghost em pixels
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE; // converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE; // converte a posição y do ghost de pixels para tiles
}

int	update_ghost(t_ghost *ghost)
{
	t_point	next;

	if (!ghost)
		return (-1);
	// if (ghost->pos.pixel_pos.x % 8 != 4 && ghost->pos.pixel_pos.y % 8 != 4)
	// {
	// 	ghost->pos.pixel_pos = continue_travel(*ghost, ghost->invalid_dir);
	// 	return 0;
	// }
	if (ghost->pos.pixel_pos.x % TILE_SIZE != TILE_SIZE / 2
		|| ghost->pos.pixel_pos.y % TILE_SIZE != TILE_SIZE / 2) // verifica se o ghost ainda não chegou ao centro do tile atual
	{
		next = continue_travel(*ghost, ghost->invalid_dir); // calcula a próxima posição do ghost ao continuar na direção atual
		ghost_set_pixel_pos(ghost, next.x, next.y); // aplica a nova posição ao ghost e sincroniza a posição em pixels com a posição em tiles
		return (0); // continua o movimento atual do ghost
	}
	ghost->invalid_dir = chose_next_move(ghost, ghost->mental_map);
	if (ghost->invalid_dir == -1)
		return (-1);
	return (0);
}

void	render_ghosts_into_framebuffer(t_game *game)
{
	int		i;
	t_point	coord;

	i = -1;
	while (++i < 4)
	{
		if(game->ghosts[i].name == DISABLED)
			continue;
		update_ghost(&game->ghosts[i]);
		coord.x = (game->ghosts[i].pos.pixel_pos.x - 8 + game->win.width / 2);
		coord.y = (game->ghosts[i].pos.pixel_pos.y - 8 + game->win.height / 2);
		render_sprite_into_framebuffer(game, coord,
			&game->ghosts[i].frames.left[0]);
	}
}

void	render_into_framebuffer(t_game *game)
{
	render_base_into_buffer(game);
	render_ghosts_into_framebuffer(game);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game, NULL);
	player_controller(game);
	render_ceiling_texture(game);
	render_floor_texture(game);
	raycast_frame(game);
	handle_gate_toggle(game);
	clear_sprite_z(game);
	render_all_sprites(game);
	render_into_framebuffer(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
		game->win.frame_buffer.img_ptr, 0, 0);
}
