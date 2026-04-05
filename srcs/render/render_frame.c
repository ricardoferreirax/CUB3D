/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/17 14:32:23 by pfreire-         ###   ########.fr       */
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

void	render_base_into_framebuffer(t_game *s)
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

t_double_point	continue_travel(t_ghost ghost, int invalid_dir)
{
	int	dir;

	dir = (invalid_dir + 2) % 4;
	int direction[4][2] = {
		{-1, 0}, // 0 = up
		{0, -1}, // 1 = left
		{1, 0},  // 2 = down
		{0, 1}   // 3 = right
	};
	ghost.speed_accumulador += ghost.speed_multiplier;
	if (ghost.speed_accumulador >= 100)
		ghost.speed_accumulador -= 100;
	if (ghost.speed_accumulador > 1)
		return ((t_double_point){.x = (ghost.pos.pixel_pos.x
				+ direction[dir][1]), .y = (ghost.pos.pixel_pos.y
				+ direction[dir][0])});
	return ((t_double_point){.x = (ghost.pos.pixel_pos.x),
		.y = (ghost.pos.pixel_pos.y)});
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

double distance_between_two_points(t_double_point point1, t_double_point point2)
{
	double distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	return distance;
}

void	ghost_move_pixel(t_ghost *gh, int dx, int dy)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x += dx;
	// adiciona o deslocamento x (pixels) à posição atual do ghost
	gh->pos.pixel_pos.y += dy;
	// adiciona o deslocamento y (pixels) à posição atual do ghost
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	// converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
	// converte a posição y do ghost de pixels para tiles
}

int	chose_next_move(t_ghost *ghost, char **map)
{
	int		i;
	int		best;
	int		best_dir;
	t_point	target;
	int		dist;

	int direction[4][2] = {
		{-1, 0}, // 0 = up
		{0, -1}, // 1 = left
		{1, 0},  // 2 = down
		{0, 1}   // 3 = right
	};

	i = 0;
	best = -1;
	best_dir = -1;
	if (!map)
		return (-1);
	target = ghost->target_tile;
	while (i < 4)
	{
		if ((map[ghost->pos.pixel_pos.y / 8
				+ direction[i][0]][ghost->pos.pixel_pos.x / 8
				+ direction[i][1]] != '1' && map[ghost->pos.pixel_pos.y / 8
				+ direction[i][0]][ghost->pos.pixel_pos.x / 8
				+ direction[i][1]] != 'G') && i != ghost->invalid_dir)
		{
			dist = (((ghost->pos.pixel_pos.x / TILE_SIZE) + direction[i][1])
					- target.x) * ((((ghost->pos.pixel_pos.x / TILE_SIZE)
							+ direction[i][1]) - target.x))
				+ ((((ghost->pos.pixel_pos.y / TILE_SIZE) + direction[i][0])
						- target.y) * ((((ghost->pos.pixel_pos.y / TILE_SIZE)
								+ direction[i][0]) - target.y)));
			{
				best = dist;
				best_dir = i;
			}
		}
		i++;
	}
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	ghost_move_pixel(ghost, direction[best_dir][1], direction[best_dir][0]);
	return ((best_dir + 2) % 4);
}


void	ghost_set_pixel_pos(t_ghost *gh, double px, double py)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x = px;
	// define a posição x do ghost em pixels
	gh->pos.pixel_pos.y = py;
	// define a posição y do ghost em pixels
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	// converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
	// converte a posição y do ghost de pixels para tiles
}

void goto_penhouse(t_game *game, t_ghost *ghost)
{
	ghost->target_tile = game->targets.ghost_house;
	ghost->speed_multiplier = 99;

}

t_point pinky_target(t_game *game)
{
	if(game->player.dir.y == 1)
		return ((t_point){.x = (game->player.pos.tile_pos.x) - 2, .y = (game->player.pos.tile_pos.y) + 2});
	if(game->player.dir.x == -1 )
		return((t_point){.x = (game->player.pos.tile_pos.x) - 2, .y = (game->player.pos.tile_pos.y) + 2});
	if(game->player.dir.y == -1)
		return ((t_point){.x = game->player.pos.tile_pos.x, .y = (game->player.pos.tile_pos.y) - 2});
	return ((t_point){.x = (game->player.pos.tile_pos.x) + 2, .y = game->player.pos.tile_pos.y});
}

int ft_abs(int n)
{
	if (n < 0)
		return -n;
	return n;
}

t_point inky_target(t_game *game)
{
	int vectorx;
	int vectory;
	t_point pinkys_target;

	pinkys_target = pinky_target(game);

	vectorx = ft_abs(game->ghosts[BLINKY].pos.tile_pos.x - pinkys_target.x);
	vectory = ft_abs(game->ghosts[BLINKY].pos.tile_pos.y - pinkys_target.y);
	vectorx *= -1;
	vectory *= -1;
	return((t_point){.x = pinkys_target.x + vectorx, .y = pinkys_target.y + vectory});
}

t_point chase_player(t_game *game, t_ghost *ghost)
{
	if(ghost->name == BLINKY)
		return ((t_point){.x = game->player.pos.tile_pos.x, .y = game->player.pos.tile_pos.y});
	if(ghost->name == PINKY)
		return (pinky_target(game));
	if (ghost->name == CLYDE)
	{
		if(distance_between_two_points(ghost->pos.tile_pos, game->player.pos.tile_pos) >= 8)
			return ((t_point){.x = game->player.pos.tile_pos.x, .y = game->player.pos.tile_pos.y});
		else
			return ((t_point){.x = game->targets.scatter_target[CLYDE].x + 0.5, .y =  game->targets.scatter_target[CLYDE].y + 0.5});
	}
	if(ghost->name == INKY)
		return(inky_target(game));
	return (t_point){0, 0};
}

void update_target(t_game *game,t_ghost *ghost, int mode)
{
	// if(mode == 2)
		// goto_penhouse(game, ghost);
	// if (mode == 1)
	// {
		// if(ghost->state == SCATTER)
		// 	ghost->state = CHASE;
		// ghost->target_tile = chase_player(game, ghost);
	// }
	(void)mode;	
	ghost->target_tile = chase_player(game, ghost);

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

	if (y < gate.y || y > gate.y + 3) // verifica se o ghost já passou em cima do gate
		return (0); // se passou, então saiu da penhouse
	return (1); // está dentro da penhouse
}
//
// static t_point	find_gate_exit(char **map)
//
// {
// 	t_point	gate; // guarda aposição do gate no mapa
//
// 	gate = find_c(map, GATE); // procura a posição do gate no mapa
// 	if (gate.x >= 0 && gate.y >= 0) // verifica se o gate foi encontrado
// 	{
// 		gate.x += 1; // move um tile para a direita do gate para encontrar o centro da porta
// 		gate.y -= 1; // move um tile para cima do gate para encontrar a posição de saída da penhouse
// 	}
// 	return (gate); // devolve o tile da saída da penhouse
// }

// int ghost_penhouse_dance(t_ghost *ghost, t_point gate)
// {
// 	if(ft_abs(ghost->pos.pixel_pos.y - ((gate.y) * TILE_SIZE)) > 1)
// 		ghost->invalid_dir = 0;
// 	else
// 		ghost->invalid_dir = 2;
// 	t_double_point next;
// 	next = continue_travel(*ghost, ghost->invalid_dir);
// 	ghost_set_pixel_pos(ghost, next.x, next.y);
// 	return 0;
//
// }

bool can_ghost_exit_penhouse(t_game *game, t_ghost *ghost)
{
	if (ghost->dot_counter < game->player.collected_dots)
		return true;
	return false;
}

int ghost_penhouse_dance(t_game *game, t_ghost *ghost, t_point gate)
{
	t_double_point	next;
	int				top_px;
	int				bottom_px;
	int				y;

	top_px = (gate.y + 1) * TILE_SIZE + TILE_SIZE / 2;
	bottom_px = (gate.y + 3) * TILE_SIZE + TILE_SIZE / 2;
	y = (int)ghost->pos.pixel_pos.y;


	if(can_ghost_exit_penhouse(game, ghost))
		ghost->invalid_dir = 2;
	else if (y <= top_px)
		ghost->invalid_dir = 0;
	else if (y >= bottom_px)
		ghost->invalid_dir = 2;

	next = continue_travel(*ghost, ghost->invalid_dir);
	ghost_set_pixel_pos(ghost, next.x, next.y);
	return (0);
}

int	update_ghost(t_game *game, t_ghost *ghost)
{
	t_double_point	next;

	if (!ghost)
		return (-1);
	if(ghost_in_penhouse(ghost, ghost->mental_map))
		return ghost_penhouse_dance(game, ghost, find_c(ghost->mental_map, 'G'));
	if (ghost->pos.pixel_pos.x % TILE_SIZE != TILE_SIZE / 2
		|| ghost->pos.pixel_pos.y % TILE_SIZE != TILE_SIZE / 2)
	{
		update_target(game, ghost, 0);
		next = continue_travel(*ghost, ghost->invalid_dir);
		ghost_set_pixel_pos(ghost, next.x, next.y);
		return (0);
		// continua o movimento atual do ghost
	}
	ghost->invalid_dir = chose_next_move(ghost, ghost->mental_map);
	if (ghost->invalid_dir == -1)
		return (-1);
	return (0);
}

void	render_ghost_into_framebuffer(t_game *game, t_point coord,
		t_ghost *ghost)
{
	if (ghost->invalid_dir == 0)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.down[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	if (ghost->invalid_dir == 1)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.right[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	if (ghost->invalid_dir == 2)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.up[((ghost->pos.pixel_pos.x + ghost->pos.pixel_pos.y)
				% 2)]);
	if (ghost->invalid_dir == 3)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.left[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
}

void	render_ghosts_into_framebuffer(t_game *game)
{
	int		i;
	t_point	coord;

	i = -1;
	while (++i < 4)
	{
		if (game->ghosts[i].name == DISABLED)
			continue ;
		ghost_wrap_position(game, &game->ghosts[i]);
		update_ghost(game, &game->ghosts[i]);
		coord.x = (game->ghosts[i].pos.pixel_pos.x - TILE_SIZE + game->win.width
				/ 2);
		coord.y = (game->ghosts[i].pos.pixel_pos.y - TILE_SIZE
				+ game->win.height / 2);
		render_ghost_into_framebuffer(game, coord, &game->ghosts[i]);
	}
}


void	render_player(t_game *game, t_point coord)
{
	if ((game->player.target_dir.y) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.down[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.right[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.y) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.up[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.left[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
}

void	render_player_into_framebuffer(t_game *game)
{
	t_point	coord;

	coord.x = (((game->player.pos.tile_pos.x - 0.5) * TILE_SIZE)
			+ game->win.width / 2) - 3;
	coord.y = (((game->player.pos.tile_pos.y - 0.5) * TILE_SIZE)
			+ game->win.height / 2) - 3;
	game->player.pos.pixel_pos.x = coord.x;
	game->player.pos.pixel_pos.y = coord.y;
	render_player(game, coord);
}

void	render_pacdots_into_framebuffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->pacdot_count)
	{
		if (game->pacdots[i].active)
			render_sprite_into_framebuffer(game,
				(t_point){.y = game->pacdots[i].pos.pixel_pos.y
				+ game->win.height / 2, .x = game->pacdots[i].pos.pixel_pos.x
				+ game->win.width / 2}, &game->sprite_sheet.sprites[37]);
		i++;
	}
}

void	render_into_framebuffer(t_game *game)
{
	render_base_into_framebuffer(game);
	render_pacdots_into_framebuffer(game);
	render_ghosts_into_framebuffer(game);
	render_player_into_framebuffer(game);
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
	// render_raycast_debug(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
		game->win.frame_buffer.img_ptr, 0, 0);
}
