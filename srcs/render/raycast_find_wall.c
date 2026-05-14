/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_find_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:39:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:57:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	ray_perp_wall_distance(t_game *g)
{
	if (g->ray.hit_side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	if (g->ray.perp_wall_dist < 1e-6)
		g->ray.perp_wall_dist = 1e-6;
}

static void	advance_ray_step(t_game *g)
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

static int	handle_ray_horizontal_wrap(t_game *g)
{
	int	last;

	if (!g || g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
		return (0);
	last = map_row_last_col(g, g->ray.map_y, 1);
	if (last >= 0)
	{
		if (g->ray.map_x < 0)
			g->ray.map_x = last;
		else if (g->ray.map_x > last)
			g->ray.map_x = 0;
		return (1);
	}
	last = map_row_last_col(g, g->ray.map_y, 0);
	if (last < 0 || g->ray.map_x < 0 || g->ray.map_x > last)
		return (0);
	return (1);
}

int	raycast_find_wall(t_game *g)
{
	int		i;
	int		limit;
	int		hit;
	char	tile;

	i = -1;
	limit = g->map.width * g->map.height + 50;
	hit = 0;
	while (++i < limit)
	{
		advance_ray_step(g);
		if (!handle_ray_horizontal_wrap(g))
			break ;
		tile = map_get_tile(g, g->ray.map_y, g->ray.map_x, 1);
		if ((tile == GATE && g->gate_passable == 0) || (tile != GATE
				&& map_tile_type(tile, TILE_SOLID)))
		{
			g->ray.hit_tile = tile;
			hit = 1;
			break ;
		}
	}
	return (hit);
}
