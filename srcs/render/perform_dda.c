/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:39:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/20 21:39:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	calculate_dda_step(t_game *g)
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
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - g->player.pos_x)
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
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - g->player.pos_y)
			* g->ray.delta_dist_y;
	}
}

static void	dda_step(t_game *g)
{
	if (g->ray.side_dist_x < g->ray.side_dist_y)
	{
		g->ray.side_dist_x += g->ray.delta_dist_x;
		g->ray.map_x += g->ray.step_x;
		g->ray.hit_side = 0;
	}
	else
	{
		g->ray.side_dist_y += g->ray.delta_dist_y;
		g->ray.map_y += g->ray.step_y;
		g->ray.hit_side = 1;
	}
}

static int	validate_or_wrap_ray(t_game *g)
{
	if (g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
		return (0);
	if (g->ray.map_x < 0 || g->ray.map_x >= g->map.width)
		return (map_wrap_ray_x(g));
	return (1);
}

int	perform_dda(t_game *g)
{
	int	steps;
	int	max_steps;
	char	t;

	steps = 0;
	max_steps = g->map.width * g->map.height + 50;
	while (steps < max_steps)
	{
		dda_step(g);
		if (!validate_or_wrap_ray(g))
			return (0);
		t = map_get_tile(g, g->ray.map_y, g->ray.map_x);
		if (map_tile_type(t, TILE_SOLID))
		{
			g->ray.hit_tile = t;
			return (1);
		}
		steps++;
	}
	return (0);
}
