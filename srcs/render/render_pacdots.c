/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pacdots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 23:53:04 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

static unsigned int	pac_tex_px(t_image *t, int x, int y)
{
	int	s;

	if (!t) 
		return (0);
	if (!t->img_addr) 
		return (0);
	s = t->l_len >> 2;
	return (((unsigned int *)t->img_addr)[y * s + x]);
}

static int	pac_project(t_game *g, t_pacdot *p)
{
	double	inv;
	double	dx;
	double	dy;

	dx = p->x - g->player.pos_x;
	dy = p->y - g->player.pos_y;
	inv = (g->player.plane_x * g->player.dir_y) - (g->player.dir_x * g->player.plane_y);
	if (inv == 0.0) 
		return (0);
	inv = 1.0 / inv;
	g->pac.depth = inv * (-g->player.plane_y * dx + g->player.plane_x * dy);
	if (g->pac.depth <= 0.001) 
		return (0);
	g->pac.sx = (int)((g->win.width / 2.0) * (1.0 + (inv * (g->player.dir_y * dx - g->player.dir_x * dy)) / g->pac.depth));
	return (1);
}

static int	pac_box(t_game *g)
{
	int	h;
	int	o;

	g->pac.size = (int)((double)g->win.height / g->pac.depth);
	if (g->pac.size < 0) 
		g->pac.size = -g->pac.size;
	g->pac.size = g->pac.size / 6;
	if (g->pac.size < 2) 
		return (0);
	h = g->win.height / 2 + 2;
	o = g->pac.size / 3;
	g->pac.y0 = h + o;
	g->pac.y1 = g->pac.y0 + g->pac.size;
	g->pac.x0 = g->pac.sx - g->pac.size / 2;
	g->pac.x1 = g->pac.sx + g->pac.size / 2;
	if (g->pac.y0 < 0) 
		g->pac.y0 = 0;
	if (g->pac.y1 >= g->win.height) 
		g->pac.y1 = g->win.height - 1;
	if (g->pac.x0 < 0) 
		g->pac.x0 = 0;
	if (g->pac.x1 >= g->win.width) 
		g->pac.x1 = g->win.width - 1;
	if (g->pac.x0 >= g->pac.x1) 
		return (0);
	if (g->pac.y0 >= g->pac.y1) 
		return (0);
	return (1);
}

static void	pac_put_sprite_col(t_game *g, unsigned int *fb, int fs, int x)
{
	int				y;
	int				tx;
	int				ty;
	unsigned int	c;

	tx = (x - g->pac.x0) * g->pac.tex.width / (g->pac.x1 - g->pac.x0);
	y = g->pac.y0;
	while (y < g->pac.y1)
	{
		ty = (y - g->pac.y0) * g->pac.tex.height / (g->pac.y1 - g->pac.y0);
		c = pac_tex_px(&g->pac.tex, tx, ty);
		if ((c & 0x00FFFFFF) != 0)
			fb[y * fs + x] = c;
		y++;
	}
}

static void	pac_draw_box(t_game *g)
{
	unsigned int	*fb;
	int				fs;
	int				x;

	fb = (unsigned int *)g->win.frame_buffer.img_addr;
	fs = g->win.frame_buffer.l_len >> 2;
	x = g->pac.x0;
	while (x < g->pac.x1)
	{
		if (g->pac.depth < g->ray.z_buffer[x])
			pac_put_sprite_col(g, fb, fs, x);
		x++;
	}
}

void	render_pacdots(t_game *g)
{
	int	i;

	if (!g) 
		return ;
	if (!g->pac.dots) 
		return ;
	if (g->pac.count <= 0) 
		return ;
	if (!g->pac.tex.img_addr) 
		return ;
	if (!g->ray.z_buffer) 
		return ;
	i = 0;
	while (i < g->pac.count)
	{
		if (g->pac.dots[i].active)
		{
			if (pac_project(g, &g->pac.dots[i]))
			{
				if (pac_box(g))
					pac_draw_box(g);
			}
		}
		i++;
	}
}
