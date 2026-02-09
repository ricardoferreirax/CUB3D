/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/21 21:08:08 by rmedeiro         ###   ########.fr       */
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

void init_ints(t_game *game)
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
	// game->win.width = TILE_SIZE * game->win.ntilesx;
	// game->win.height = TILE_SIZE * game->win.ntilesy;
	game->win.width = 1280;
	game->win.height = 800;
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
		init_ghost(game, &game->ghost[i]);
}

int uselesstile(t_point point)
{
	if(point.y == 55)
	{
		if(point.x == 154 || point.x == 163)
			return 1;
	}
	return 0;
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
		while (control.x < 373)
		{
			if(!uselesstile(control))
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
	while(control.y <= 168)
	{
		control.x = 1;
		while(control.x < 574)
		{
			game->sprite_sheet.sprites[i].coord = control;
			game->sprite_sheet.sprites[i].width = 16;
			game->sprite_sheet.sprites[i].height = 16;
			control.x += 17;
		}
		control.y += 17;
	}
	return i;
}

void	init_render(t_game *g)
{
	g->render.width = g->win.width;
	g->render.height = g->win.height;
	g->render.img_ptr = mlx_new_image(g->mlx_ptr, g->render.width, g->render.height);
	if (!g->render.img_ptr)
		exit_game(EXIT_MLX, g);
	g->render.img_addr = mlx_get_data_addr(g->render.img_ptr, &g->render.bpp, &g->render.l_len,
		&g->render.endian);
	if (!g->render.img_addr)
		exit_game(EXIT_MLX, g);
}

void	init_game(t_game *game)
{
	init_null(game);
	init_window(game);
	// init_ghosts(game);
	// init_spritesheet(game);
	init_render(game);
}
