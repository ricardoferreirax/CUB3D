/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/14 16:10:08 by pfreire-         ###   ########.fr       */
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

int	keyloop(int key, t_game *game)
{
	if (key == 0 && game->debug_mode)
		ft_printf("test");
	if (key == 'q' || key == 65307)
		ft_printf("test");
	else if (key == 0 || key == 0)
	{
		ft_printf("test");
	}
	else if (key == 0 || key == 0)
	{
		ft_printf("test");
	}
	else if (key == 0 || key == 0)
	{
		ft_printf("test");
	}
	else if (key == 0 || key == 0)
	{
		ft_printf("test");
	}
	return (0);
}

char	**map_parser(char **argv)
{
	int		fd;
	char	**line_test;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_test = ft_calloc(sizeof(char *), 100);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		line_test[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (line_test);
}

void	print_2d(char **map)
{
	char	buffer[4096];
	int		offset;

	offset = 0;
	for (int i = 0; map[i]; i++)
		offset += sprintf(buffer + offset, "%s", map[i]);
	write(1, buffer, offset);
}

int	close_game(void *game)
{
	(void)game;
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if ((argc > 3 || argc == 1) || (argc == 3 && (ft_strcmp(argv[2],
					"debug_mode=y") != 0)))
		return (ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_dprintf(2, "No Memory, Download more RAM\n"), -1);
	game->map.grid = map_parser(argv);
	game->debug_mode = false;
	init_game(game);
	game->mlx_ptr = mlx_init();
	mlx_key_hook(game->win.win_ptr, keyloop, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_hook(game->win.win_ptr, 17, 0, close_game, game);
	mlx_loop(game->mlx_ptr);
}
