/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_defaults.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:09 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 20:56:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	init_view(t_game *g)
{
	// posição inicial provisória
	g->view.x = 1.5;
	g->view.y = 1.5;

	// direção inicial (olhar para +X)
	g->view.dir_x = 1.0;
	g->view.dir_y = 0.0;

	// plano da camara (fov ~66°)
	g->view.plane_x = 0.0;
	g->view.plane_y = 0.66;
}

static void	init_window_struct(t_game *g)
{
	// window
	g->win.win_ptr = NULL;
	g->win.width = 0;
	g->win.height = 0;
	g->win.ntilesx = 0;
	g->win.ntilesy = 0;

	// frame buffer 
	g->win.frame_buffer.img_ptr = NULL;
	g->win.frame_buffer.img_addr = NULL;
	g->win.frame_buffer.bpp = 0;
	g->win.frame_buffer.l_len = 0;
	g->win.frame_buffer.endian = 0;
	g->win.frame_buffer.width = 0;
	g->win.frame_buffer.height = 0;
}

static void	init_map_struct(t_game *g)
{
	g->map.grid = NULL;
	g->map.width = 0;
	g->map.height = 0;
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
	g->ray.side = 0;
	g->ray.perp_wall_dist = 0.0;
	g->ray.draw_start = 0;
	g->ray.draw_end = 0;
}

void	init_defaults(t_game *g)
{
	if (!g)
		return ;
	g->mlx_ptr = NULL;
	init_window_struct(g);
	init_map_struct(g);
	init_keys(g);
	init_view(g);
	init_raycasting(g);
}
