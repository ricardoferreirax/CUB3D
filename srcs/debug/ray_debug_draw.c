/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:45:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:45:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	debug_fill_cell(t_game *g, t_point p, int color)
{
	t_point	i;

	i.y = 0;
	while (i.y < DEBUG_CELL)
	{
		i.x = 0;
		while (i.x < DEBUG_CELL)
		{
			debug_put_pixel(g, debug_point(p.x + i.x, p.y + i.y), color);
			i.x++;
		}
		i.y++;
	}
}

void	debug_draw_hit_marker(t_game *g, t_point p)
{
	t_point	i;

	i.y = 0;
	while (i.y < 3)
	{
		i.x = 0;
		while (i.x < 3)
		{
			debug_put_pixel(g, debug_point(p.x - 1 + i.x, p.y - 1 + i.y),
				DEBUG_COLOR_HIT);
			i.x++;
		}
		i.y++;
	}
}

void	debug_draw_player_marker(t_game *g, t_point p)
{
	t_point	i;

	i.y = 0;
	while (i.y < 5)
	{
		i.x = 0;
		while (i.x < 5)
		{
			debug_put_pixel(g, debug_point(p.x - 2 + i.x, p.y - 2 + i.y),
				DEBUG_COLOR_PLAYER);
			i.x++;
		}
		i.y++;
	}
}

void	debug_draw_tile(t_game *g, int x, int y)
{
	t_point	p;
	int		color;

	p.x = DEBUG_OFF_X + x * DEBUG_CELL;
	p.y = DEBUG_OFF_Y + y * DEBUG_CELL;
	color = debug_get_tile_color(g, x, y);
	debug_fill_cell(g, p, color);
	debug_put_pixel(g, p, DEBUG_COLOR_GRID);
}

void	debug_draw_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			debug_draw_tile(g, x, y);
			x++;
		}
		y++;
	}
}
