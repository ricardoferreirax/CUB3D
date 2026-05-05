/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:44:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:45:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int	debug_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_point	debug_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point	debug_world_to_screen(double x, double y)
{
	t_point	p;

	p.x = DEBUG_OFF_X + (int)(x * DEBUG_CELL);
	p.y = DEBUG_OFF_Y + (int)(y * DEBUG_CELL);
	return (p);
}

void	debug_put_pixel(t_game *g, t_point p, int color)
{
	if (!g)
		return ;
	if (p.x < 0 || p.y < 0)
		return ;
	if (p.x >= g->win.width || p.y >= g->win.height)
		return ;
	ft_pixel_put(&g->win.frame_buffer, p.x, p.y, color);
}

int	debug_get_tile_color(t_game *g, int x, int y)
{
	char	tile;

	tile = map_get_tile(g, y, x);
	if (map_tile_type(tile, TILE_SOLID) || tile == GATE)
		return (DEBUG_COLOR_WALL);
	return (DEBUG_COLOR_BG);
}
