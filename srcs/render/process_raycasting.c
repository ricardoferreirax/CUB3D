/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 22:43:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

static void	cal_draw_range(t_game *g)
{
	int	col_height;

	col_height = (int)((double)g->win.height / g->ray.perp_wall_dist);
	if (col_height < 1)
		col_height = 1;
	g->ray.line_h = col_height;
	g->ray.draw_start = g->win.height / 2 - col_height / 2;
	g->ray.draw_end = g->win.height / 2 + col_height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

static void calc_perp_wall_distance(t_game *g) 
{ 
	if (g->ray.hit_side == 0) 
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x; 
	else 
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y; 
	if (g->ray.perp_wall_dist < 1e-6) 
 		g->ray.perp_wall_dist = 1e-6; 
}

void	dda_init_steps(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos_x - g->ray.map_x)
			* g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + TILE_SIZE_3D - g->player.pos_x)
			* g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos_y - g->ray.map_y)
			* g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + TILE_SIZE_3D - g->player.pos_y)
			* g->ray.delta_dist_y;
	}
}

static void	init_ray_column(t_game *g, int col)
{
	double	cam_x;

	cam_x = 2.0 * col / (double)g->win.width - 1.0;
	g->ray.camera_x = cam_x;
	g->ray.ray_dir_x = g->player.dir_x + g->player.plane_x * cam_x;
	g->ray.ray_dir_y = g->player.dir_y + g->player.plane_y * cam_x;
	g->ray.map_x = (int)g->player.pos_x;
	g->ray.map_y = (int)g->player.pos_y;
	g->ray.hit = 0;
	g->ray.hit_side = 0;
	g->ray.hit_tile = VOID;
	if (g->ray.ray_dir_x == 0.0)
		g->ray.delta_dist_x = 1e30;
	else
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (g->ray.ray_dir_y == 0.0)
		g->ray.delta_dist_y = 1e30;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

void	process_raycasting(t_game *g)
{
	int	col;
	int	center_hit;

	if (!g)
		return ;
	col = -1;
	center_hit = 0;
	while (++col < g->win.width)
	{
		init_ray_column(g, col);
		dda_init_steps(g);
		if (perform_dda(g)) // se bateu numa parede renderiza a coluna caso contrario passa para a próxima
		{
			calc_perp_wall_distance(g);
			cal_draw_range(g);
			render_wall_col(g, col);
			g->ray.z_buffer[col] = g->ray.perp_wall_dist;
			center_hit = register_center_hit(g, col, center_hit);
		}
	}
}
