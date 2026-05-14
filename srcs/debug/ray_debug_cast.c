/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:46:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:58:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static int	debug_tile_color(t_game *g, int x, int y)
{
	char	tile;

	tile = map_get_tile(g, y, x, 0);
	if (map_tile_type(tile, TILE_SOLID) || tile == GATE)
		return (DEBUG_WALL);
	return (DEBUG_BG);
}

static void	debug_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			debug_square(g, debug_pos(x, y), DEBUG_CELL - 1,
				debug_tile_color(g, x, y));
			x++;
		}
		y++;
	}
}

int	debug_ray(t_game *g, int col, t_raycasting *ray)
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

static void	debug_draw_ray(t_game *g, t_point start, t_raycasting ray)
{
	t_point	end;

	end = debug_pos(g->player.pos.tile_pos.x
			+ ray.perp_wall_dist * ray.ray_dir_x,
			g->player.pos.tile_pos.y
			+ ray.perp_wall_dist * ray.ray_dir_y);
	debug_line(g, start, end);
	debug_square(g, (t_point){end.x - 1, end.y - 1}, 3, DEBUG_HIT);
}

void	render_raycast_debug(t_game *g)
{
	t_raycasting	ray;
	t_point			start;
	int				col;

	if (!g)
		return ;
	debug_map(g);
	start = debug_pos(g->player.pos.tile_pos.x, g->player.pos.tile_pos.y);
	col = 0;
	while (col < g->win.width)
	{
		if (debug_ray(g, col, &ray))
			debug_draw_ray(g, start, ray);
		col += DEBUG_RAY_STEP;
	}
	debug_square(g, (t_point){start.x - 2, start.y - 2}, 5, DEBUG_PLAYER);
}
