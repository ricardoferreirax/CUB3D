/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 21:05:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	init_dda(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->view.x - g->ray.map_x) * g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - g->view.x) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->view.y - g->ray.map_y) * g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - g->view.y) * g->ray.delta_dist_y;
	}
}

static void	init_ray(t_game *g, int x)
{
	g->ray.camera_x = 2.0 * x / (double)g->render.width - 1.0;
	g->ray.ray_dir_x = g->view.dir_x + g->view.plane_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->view.dir_y + g->view.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)g->view.x;
	g->ray.map_y = (int)g->view.y;
	g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

void	render_3d(t_game *g)
{
	int	x;

	x = 0;
	while (x < g->render.width)
	{
		init_ray(g, x);
		init_dda(g);
		// perform_dda(g);
		// calc_wall_distance(g);
		// calc_draw_limits(g);
		// draw_vertical_line(g, x);
		g->ray.z_buffer[x] = g->ray.perp_wall_dist;
		x++;
	}
}
