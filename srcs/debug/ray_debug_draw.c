/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:45:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 18:32:14 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

t_point	debug_pos(double x, double y)
{
	t_point	p;

	p.x = DEBUG_OFF_X + (int)(x * DEBUG_CELL);
	p.y = DEBUG_OFF_Y + (int)(y * DEBUG_CELL);
	return (p);
}

static void	debug_pixel(t_game *g, int x, int y, int color)
{
	if (!g || x < 0 || y < 0)
		return ;
	if (x >= g->win.width || y >= g->win.height)
		return ;
	ft_pixel_put(&g->win.frame_buffer, x, y, color);
}

void	debug_square(t_game *g, t_point p, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			debug_pixel(g, p.x + x, p.y + y, color);
			x++;
		}
		y++;
	}
}

void	debug_line(t_game *g, t_point a, t_point b)
{
	double	dx;
	double	dy;
	double	step;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	step = fabs(dx);
	if (fabs(dy) > step)
		step = fabs(dy);
	i = 0;
	while (i <= (int)step)
	{
		debug_pixel(g, a.x + (int)(dx * i / step),
			a.y + (int)(dy * i / step), DEBUG_RAY);
		i++;
	}
}
