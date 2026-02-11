/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/10 14:00:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

// static void	init_window_struct(t_game *g)
// {
// 	g->win.win_ptr = NULL;
// 	g->win.width = 0;
// 	g->win.height = 0;
// 	g->win.ntilesx = 0;
// 	g->win.ntilesy = 0;
//
// 	g->win.frame_buffer.img_ptr = NULL;
// 	g->win.frame_buffer.img_addr = NULL;
// 	g->win.frame_buffer.bpp = 0;
// 	g->win.frame_buffer.l_len = 0;
// 	g->win.frame_buffer.endian = 0;
// 	g->win.frame_buffer.width = 0;
// 	g->win.frame_buffer.height = 0;
// }

// static void	init_map_struct(t_game *g)
// {
// 	g->map.grid = NULL;
// 	g->map.width = 0;
// 	g->map.height = 0;
// }

static void	init_player_raycast_state(t_game *g)
{
	g->player.target_map_x = -1;
	g->player.target_map_y = -1;
	g->player.target_tile = '0';
	g->player.target_wall_dir = 0;
	g->player.target_dist = 0.0;
}

static void	init_raycasting(t_game *g)
{
	g->ray.z_buffer = NULL;
	g->ray.camera_x = 0.0;
	g->ray.ray_dir_x = 0.0;
	g->ray.ray_dir_y = 0.0;
	g->ray.map_x = 0;
	g->ray.map_y = 0;
	g->ray.step_x = 0;
	g->ray.step_y = 0;
	g->ray.side_dist_x = 0.0;
	g->ray.side_dist_y = 0.0;
	g->ray.delta_dist_x = 0.0;
	g->ray.delta_dist_y = 0.0;
	g->ray.hit_side = -1;
	g->ray.perp_wall_dist = 0.0;
	g->ray.draw_start = 0;
	g->ray.draw_end = 0;
}

static void	init_render_struct(t_game *g)
{
	g->render.width = 0;
	g->render.height = 0;
	g->render.img_ptr = NULL;
	g->render.img_addr = NULL;
	g->render.bpp = 0;
	g->render.l_len = 0;
	g->render.endian = 0;
}

void	init_ints(t_game *game)
{
	game->global_dot_counter = 0;
	game->timeout = 0;
	game->score = 0;
	game->level = 0;
	game->timer.level_time = 0;
	game->timer.mode_timer = 0;
	game->timer.timeout_timer = 0;
	game->timer.last_time_up = 0;
	game->timer.accumulator = 0;
}

void	init_null(t_game *g)
{
	init_ints(g);
	// init_window_struct(g);
	init_render_struct(g);
	// init_map_struct(g);
	init_keys(g);
	init_raycasting(g);
	init_player_raycast_state(g);
}

void	init_window(t_game *game)
{
	game->win.ntilesx = xtile(game->map.grid);
	game->win.ntilesy = ytile(game->map.grid);
	game->win.width = 1280;
	game->win.height = 1080;
	game->win.win_ptr = mlx_new_window(game->mlx_ptr, game->win.width,
			game->win.height, "Pac-Man");
	game->win.frame_buffer.img_ptr = mlx_new_image(game->mlx_ptr,
			game->win.width, game->win.height);
	game->win.frame_buffer.img_addr = mlx_get_data_addr(game->win.frame_buffer.img_ptr,
			&game->win.frame_buffer.bpp, &game->win.frame_buffer.l_len,
			&game->win.frame_buffer.endian);
	game->win.frame_buffer.width = game->win.width;
	game->win.frame_buffer.height = game->win.height;
}

void	init_ghost(t_game *game, t_ghost *ghost)
{
	ghost->is_steping_on_pacdot = 0;
	ghost->mental_map = copy_map(game->map.grid);
	ghost->state = SCATTER;
	if (ghost->name == BLINKY)
		init_blinky(game, ghost);
	if (ghost->name == PINKY)
		init_pinky(game, ghost);
	if (ghost->name == INKY)
		init_inky(game, ghost);
	if (ghost->name == CLYDE)
		init_clyde(game, ghost);
}

void	init_ghosts(t_game *game)
{
	int	i;

	game->ghost = malloc(sizeof(t_ghost) * 4);
	i = -1;
	while (++i < 4)
	{
		game->ghost[i].name = BLINKY;
		init_ghost(game, &game->ghost[i]);
	}
}

int	uselesstile(t_point point)
{
	if (point.y == 55)
	{
		if (point.x == 154 || point.x == 163)
			return (1);
	}
	return (0);
}

int	init_spritesheet(t_game *game)
{
	t_point	control;
	int		i;

	game->sprite_sheet.sprites = malloc(sizeof(t_sprite_ref) * 256);
	i = 0;
	control.y = 1;
	while (control.y <= 74)
	{
		control.x = 1;
		while (control.x < 199)
		{
			if (!uselesstile(control))
			{
				game->sprite_sheet.sprites[i].coord = control;
				game->sprite_sheet.sprites[i].width = 8;
				game->sprite_sheet.sprites[i].height = 8;
				i++;
			}
			control.x += 9;
		}
		control.y += 9;
	}
	control.y = 83;
	while (control.y <= 168)
	{
		control.x = 1;
		while (control.x < 170)
		{
			game->sprite_sheet.sprites[i].coord = control;
			game->sprite_sheet.sprites[i].width = 16;
			game->sprite_sheet.sprites[i].height = 16;
			i++;
			control.x += 17;
		}
		control.y += 17;
	}
	game->sprite_sheet.sprite_img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, SPRITE_SHEET, &game->sprite_sheet.sprite_img.width, &game->sprite_sheet.sprite_img.height);
	if (!game->sprite_sheet.sprite_img.img_ptr)
		exit(ft_printf("Did not found SpriteSheet.xpm\n"));
	game->sprite_sheet.sprite_img.img_addr = mlx_get_data_addr(game->sprite_sheet.sprite_img.img_ptr, &game->sprite_sheet.sprite_img.bpp, &game->sprite_sheet.sprite_img.l_len, &game->sprite_sheet.sprite_img.endian);
	return (i);
}

void	init_render(t_game *g)
{
	g->render.width = g->win.width;
	g->render.height = g->win.height;
	g->render.img_ptr = mlx_new_image(g->mlx_ptr, g->render.width,
			g->render.height);
	if (!g->render.img_ptr)
		exit_game(EXIT_MLX, g);
	g->render.img_addr = mlx_get_data_addr(g->render.img_ptr, &g->render.bpp,
			&g->render.l_len, &g->render.endian);
	if (!g->render.img_addr)
		exit_game(EXIT_MLX, g);
}

void	fill_tile(t_game *g, t_image *tile, unsigned int color, t_point point)
{
	int	ty;
	int	tx;

	ty = 0;
	while (ty < tile->height)
	{
		tx = 0;
		while (tx < tile->width)
		{
			color = pixel_get(tile, tx, ty);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&g->base, point.x + tx, point.y + ty, color);
			tx++;
		}
		ty++;
	}
}

int which_tile(t_game *game, t_point coord)
{
	if(game->map.grid[coord.y][coord.x] != '1')
		return(90);
	else
		return(39);
}

void put_tile_inbase(t_game *g, int tile_code, unsigned int color, t_point point)
{
	int ty;
	int tx;

	ty = 0;
	while(ty < g->sprite_sheet.sprites[tile_code].height)
	{
		tx = 0;
		while(tx < g->sprite_sheet.sprites[tile_code].width)
		{
			color = pixel_get(&g->sprite_sheet.sprite_img, g->sprite_sheet.sprites[tile_code].coord.x + 400 + tx, g->sprite_sheet.sprites[tile_code].coord.y + 186  + ty);
			if((color >> 24) != 0xFF)
				ft_pixel_put(&g->base, point.x * 8 + tx, point.y * 8 + ty, color);
			tx++;
		}
		ty++;
	}
}

void	init_base(t_game *s)
{
	int			tile;
	t_point			point;
	unsigned int	color;

	color = 0;
	point.x = 0;
	point.y = 0;
	s->base.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width, s->win.height);
	s->base.img_addr = mlx_get_data_addr(s->base.img_ptr, &s->base.bpp,
			&s->base.l_len, &s->base.endian);
	s->base.width = s->map.width * TILE_SIZE;
	s->base.height = s->map.height * TILE_SIZE;
	while(s->map.grid[point.y])
	{
		point.x = 0;
		while(s->map.grid[point.y][point.x])
		{
			tile = which_tile(s, point);
			put_tile_inbase(s, tile, color, point);
			point.x++;
		}
		point.y++;
	}
}

void	init_game(t_game *game)
{
	init_null(game);
	init_window(game);
	init_ghosts(game);
	init_spritesheet(game);
	init_base(game);
	init_render(game);
}
