/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 21:30:19 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

static void	calc_draw_limits(t_game *g)
{
	int	line_h;

	line_h = (int)((double)g->win.height / g->ray.perp_wall_dist);
	if (line_h < 1)
		line_h = 1;
	g->ray.line_h = line_h;
	g->ray.draw_start = -line_h / 2 + g->win.height / 2;
	g->ray.draw_end = line_h / 2 + g->win.height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

static void calc_wall_distance(t_game *g) 
{ 
	if (g->ray.hit_side == 0) 
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x; 
	else 
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y; 
	if (g->ray.perp_wall_dist < 1e-6) 
 		g->ray.perp_wall_dist = 1e-6; 
}

static void	init_ray(t_game *g, int x)
{
	g->ray.camera_x = 2.0 * x / (double)g->win.width - 1.0;
	g->ray.ray_dir_x = g->player.dir_x + g->player.plane_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->player.dir_y + g->player.plane_y * g->ray.camera_x;
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
	int	screen_x;
	int	hit_found;
	int	hit;

	if (!g)
		return ;
	screen_x = 0;
	hit_found = 0;
	while (screen_x < g->win.width)
	{
		init_ray(g, screen_x);
		calculate_dda_step(g);
		hit = perform_dda(g);
		if (hit)
		{
			calc_wall_distance(g);
			calc_draw_limits(g);
			render_wall_col(g, screen_x);
			g->ray.z_buffer[screen_x] = g->ray.perp_wall_dist;
			hit_found = register_center_hit(g, screen_x, hit_found);
		}
		screen_x++;
	}
}

