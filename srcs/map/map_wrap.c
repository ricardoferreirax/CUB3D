/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/20 23:40:36 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	map_is_wrap_port(t_game *g, int y, int x)
{
	if (map_get_tile(g, y, 0) != WRAP_PORTS)
		return (0);
	if (map_get_tile(g, y, g->map.width - 1) != WRAP_PORTS)
		return (0);
	if (x != 0 && x != g->map.width - 1)
		return (0);
	if (map_tile_type(map_get_tile(g, y - 1, x), TILE_VOID)
		|| map_tile_type(map_get_tile(g, y + 1, x), TILE_VOID))
		return (0);
	if (x == 0 && !map_tile_type(map_get_tile(g, y, 1), TILE_WALKABLE))
		return (0);
	if (x == g->map.width - 1
		&& !map_tile_type(map_get_tile(g, y, g->map.width - 2), TILE_WALKABLE))
		return (0);
	return (1);
}

int	map_wrap_row_is_active(t_game *g, int y)
{
	if (!g || !g->map.grid)
		return (0);
	if (y < 0 || y >= g->map.height)
		return (0);
	if (g->map.width <= 1)
		return (0);
	return (g->map.grid[y][0] == WRAP_PORTS
		&& g->map.grid[y][g->map.width - 1] == WRAP_PORTS);
}

double	wrap_dx(t_game *g, double x, double y)
{
	double	dx;
	double	w;
	int		row;

	dx = x - g->player.pos_x;
	if (!g)
		return (dx);
	row = (int)g->player.pos_y;
	if ((int)y != row)
		return (dx);
	if (!map_wrap_row_is_active(g, row))
		return (dx);
	w = (double)g->map.width;
	if (dx > w / 2.0)
		dx -= w;
	else if (dx < -w / 2.0)
		dx += w;
	return (dx);
}

int	map_wrap_ray_x(t_game *g)
{
	int	w;

	if (!g)
		return (0);
	if (!map_wrap_row_is_active(g, g->ray.map_y))
		return (0);
	w = g->map.width;
	if (g->ray.map_x < 0)
	{
		g->ray.map_x = w - 1;
		return (1);
	}
	if (g->ray.map_x >= w)
	{
		g->ray.map_x = 0;
		return (1);
	}
	return (1);
}

void	map_wrap_port(t_game *g)
{
	int		y;
	int		w;

	if (!g)
		return ;
	y = (int)g->player.pos_y;
	if (!map_wrap_row_is_active(g, y))
		return ;
	w = g->map.width;
	if (g->player.pos_x < 0.0)
		g->player.pos_x += (double)w;
	else if (g->player.pos_x >= (double)w)
		g->player.pos_x -= (double)w;
}
