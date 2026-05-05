/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:46:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:46:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

t_point	debug_get_line_delta(t_point a, t_point b)
{
	t_point	d;

	d.x = debug_abs(b.x - a.x);
	d.y = debug_abs(b.y - a.y);
	return (d);
}

t_point	debug_get_line_step(t_point a, t_point b)
{
	t_point	s;

	s.x = -1;
	s.y = -1;
	if (a.x < b.x)
		s.x = 1;
	if (a.y < b.y)
		s.y = 1;
	return (s);
}

void	debug_advance_line(t_point *p, t_point d, t_point s, int *err)
{
	int	e2;

	e2 = (*err) * 2;
	if (e2 > -d.y)
	{
		*err -= d.y;
		p->x += s.x;
	}
	if (e2 < d.x)
	{
		*err += d.x;
		p->y += s.y;
	}
}

void	debug_draw_ray_line(t_game *g, t_point a, t_point b)
{
	t_point	d;
	t_point	s;
	t_point	p;
	int		err;

	p = a;
	d = debug_get_line_delta(a, b);
	s = debug_get_line_step(a, b);
	err = d.x - d.y;
	while (1)
	{
		debug_put_pixel(g, p, DEBUG_COLOR_RAY);
		if (p.x == b.x && p.y == b.y)
			break ;
		debug_advance_line(&p, d, s, &err);
	}
}
