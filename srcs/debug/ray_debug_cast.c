/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:46:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:46:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int	debug_cast_screen_ray(t_game *g, int col, t_raycasting *ray)
{
	t_raycasting	saved;

	saved = g->ray;
	ray_init(g, col);
	ray_init_steps(g);
	if (!raycast_find_wall(g))
	{
		g->ray = saved;
		return (0);
	}
	ray_perp_wall_distance(g);
	*ray = g->ray;
	g->ray = saved;
	return (1);
}

t_point	debug_get_ray_hit_point(t_game *g, t_raycasting ray)
{
	double	x;
	double	y;

	x = g->player.pos.tile_pos.x + ray.perp_wall_dist * ray.ray_dir_x;
	y = g->player.pos.tile_pos.y + ray.perp_wall_dist * ray.ray_dir_y;
	return (debug_world_to_screen(x, y));
}

void	debug_draw_casted_ray(t_game *g, t_point start, t_raycasting ray)
{
	t_point	end;

	end = debug_get_ray_hit_point(g, ray);
	debug_draw_ray_line(g, start, end);
	debug_draw_hit_marker(g, end);
}
