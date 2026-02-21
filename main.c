/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/21 23:49:19 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"
#include "srcs/text/textures3D.h"
#include "srcs/render/render3D.h"
#include "srcs/map/map3D.h"

int	gameloop(t_game *game)
{
	long	now;

	now = get_time_us();
	if (game->timer.last_time_up == 0)
	{
		game->timer.last_time_up = now;
		return (0);
	}
	game->timer.last_time_up = now;
	render_frame(game);
	return (0);
}

void	parse_map(t_game *g, const char *path)
{

	char	**rect;

	g->map.grid = load_map_from_cub(g, path);
	if (!g->map.grid)
		exit_game(EXIT_MAP, g);
	map_setup_size(g);
	rect = map_rectangular(g);
	if (!rect)
		exit_game(EXIT_MALLOC, g);
	free_tab_tab(g->map.grid);
	g->map.grid = rect;
	map_validate_chars(g);
	init_player_from_map(g);
	map_validate_closed(g);
}

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g);
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
	g->ray.sprite_z = malloc(sizeof(double) * g->win.width * g->win.height);
	if (!g->ray.sprite_z)
		exit_game(EXIT_MALLOC, g);
}

void	init_defaults(t_game *g)
{
	if (!g)
		return ;
	ft_bzero(g, sizeof(t_game));
	g->ray.hit_side = -1;
	g->player.target_map_x = -1;
	g->player.target_map_y = -1;
	g->map.floor_color = -1;
	g->map.ceiling_color = -1;
	g->gate_passable = 0;
}

int main(int ac, char **av)
{
	t_game *game;
	if((ac > 3 || ac == 1) || (ac == 3 && (ft_strcmp(av[2], "debug_mode=y") != 0)))
		return(ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(EXIT_MALLOC, NULL);
	init_defaults(game);
	parse_texture(game, av[1]);
	parse_map(game, av[1]);
	init_mlx(game);
	init_assets(game);

	start_execution(game);
	
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}


/* void	clear_terminal(void)
{
	write(1, "\033[H", 3);
}

void	ft_pixel_put(t_image *s, int x, int y, unsigned int color)
{
	char	*dest;

	dest = s->img_addr + (y * s->l_len + x * (s->bpp / 8));
	*(unsigned int *)dest = color;
}

int	pixeL_get_coord(t_sprite_sheet *sheet, int i, int x, int y)
{
	char	*dest;

	dest = sheet->sprite_img.img_addr + ((sheet->sprites[i].coord.y + y)
			* sheet->sprite_img.l_len + (sheet->sprites[i].coord.x + x)
			* (sheet->sprite_img.bpp / 8));
	return (*(unsigned int *)dest);
}

int	pixel_get(t_image *data, int x, int y)
{
	char	*dest;

	dest = data->img_addr + (y * data->l_len + x * (data->bpp / 8));
	return (*(unsigned int *)dest);
}

void	new_target(t_game *game, t_ghost *ghost, e_state state)
{
	if (state == SCATTER)
		ghost->target_tile = find_c(game->map.grid, 'S');
	if (state == CHASE)
		ghost->target_tile = find_c(game->map.grid, 'J');
	if (state == SCATTER)
	{
		if (ghost->name == BLINKY)
			ghost->target_tile = find_c(game->map.grid, 'B');
		if (ghost->name == PINKY)
			ghost->target_tile = find_c(game->map.grid, 'P');
		if (ghost->name == INKY)
			ghost->target_tile = find_c(game->map.grid, 'I');
		if (ghost->name == CLYDE)
			ghost->target_tile = find_c(game->map.grid, 'C');
	}
}

void	update_target(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		new_target(game, &game->ghost[i], game->ghost[i].state);
		i++;
	}
}

void	update_game(t_game *game)
{
	int		i;
	t_point	next_move;
		char c;

	i = 0;
	while (i < 4)
	{
		next_move = chose_next_move(&game->ghost[i], game->ghost->mental_map);
		game->map.grid[game->ghost[i].pos.tile_pos.y][game->ghost[i].pos.tile_pos.x] = '0';
		game->ghost[i].pos.pixel_pos.x += next_move.x;
		game->ghost[i].pos.pixel_pos.y += next_move.y;
		game->ghost[i].pos.tile_pos.x = game->ghost[i].pos.pixel_pos.x / 8;
		game->ghost[i].pos.tile_pos.y = game->ghost[i].pos.pixel_pos.y / 8;
		if (i == 0)
			c = 'L';
		if (i == 1)
			c = 'N';
		if (i == 2)
			c = 'K';
		if (i == 3)
			c = 'Y';
		game->map.grid[game->ghost[i].pos.tile_pos.y][game->ghost[i].pos.tile_pos.x] = c;
		i++;
	}
}

void	clear_frame(t_game *s)
{
	size_t	bytes;

	bytes = (size_t)(s->win.frame_buffer.l_len * s->win.frame_buffer.height);
	ft_bzero(s->win.frame_buffer.img_addr, bytes);
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
				ft_pixel_put(&s->win.frame_buffer, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_game(t_game *game)
{
	clear_frame(game);
	render_base_into_buffer(game);
	return ;
}

int	close_game(void *game)
{
	(void)game;
	exit(1);
} */
