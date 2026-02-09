/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/29 21:16:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

void	clear_terminal(void)
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
}

int	gameloop(t_game *game)
{
	long	now;
	long	delta;
	int		updates;

	updates = 0;
	now = get_time_us();
	if (game->timer.last_time_up == 0)
	{
		game->timer.last_time_up = now;
		return (0);
	}
	delta = now - game->timer.last_time_up;
	if (delta > 250000)
		delta = 250000;
	game->timer.accumulator += delta;
	while (game->timer.accumulator >= UPDATE_F && updates < MAX_UPDATES)
	{
		update_game(game);
		game->timer.accumulator -= UPDATE_F;
		updates++;
	}
	render_game(game);
	return (0);
	// update_target(game);

	return (0);
}

void	parse_map(t_game *g, const char *path)
{

	char	**rect;

	g->map.grid = map_read_file(path);
	if (!g->map.grid)
		exit_game(EXIT_MAP, g);
	setup_map_grid(g);
	rect = map_rectangular(g);
	if (!rect)
		exit_game(EXIT_MALLOC, g);
	free_tab_tab(g->map.grid);
	g->map.grid = rect;
	validate_map_chars(g);
	init_player_from_map(g);
	validate_map_closed(g);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if ((argc > 3 || argc == 1) || (argc == 3 && (ft_strcmp(argv[2],
					"debug_mode=y") != 0)))
		return (ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_dprintf(3, "No Memory, Download more RAM\n"), exit_game(EXIT_MALLOC, NULL), -1);
	parse_map(game, argv[1]);
	game->debug_mode = false;
	init_game(game);
	parse_map(game, argv[1]);
	game->mlx_ptr = mlx_init();
	start_execution(game);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	

	return (0);
}


