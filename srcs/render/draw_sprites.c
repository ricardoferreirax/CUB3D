/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 20:58:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static unsigned int	sprite_tex_px(t_image *t, int x, int y)
{
	int	s;

	if (!t || !t->img_addr)
		return (0);
	s = t->l_len >> 2;
	return (((unsigned int *)t->img_addr)[y * s + x]);
}

int	sprite_project(t_game *g, double x, double y, t_sprite *b)
{
	double	inv;
	double	dx;
	double	dy;

	dx = x - g->player.pos_x;
	dy = y - g->player.pos_y;
	inv = (g->player.plane_x * g->player.dir_y) - (g->player.dir_x * g->player.plane_y);
	if (inv == 0.0)
		return (0);
	inv = 1.0 / inv;
	b->depth = inv * (-g->player.plane_y * dx + g->player.plane_x * dy);
	if (b->depth <= 0.001)
		return (0);
	b->screen_x = (int)((g->win.width / 2.0) * (1.0 + (inv * (g->player.dir_y * dx
			- g->player.dir_x * dy)) / b->depth));
	return (1);
}

int	sprite_build(t_game *g, t_sprite *b, int size_div)
{
	int		horizon;
	int		v_move_screen;
	double	v_move_world;

	b->size = (int)((double)g->win.height / b->depth);
	if (b->size < 0)
		b->size = -b->size;
	b->size /= size_div;
	if (b->size < 2)
		return (0);
	horizon = g->win.height / 2;
	v_move_world = 0.10;
	v_move_screen = (int)(v_move_world * ((double)g->win.height) / b->depth);
	b->raw_x0 = b->screen_x - b->size / 2;
	b->y1 = horizon + (b->size / 2) + v_move_screen;
	b->raw_y0 = b->y1 - b->size;
	b->x0 = b->raw_x0;
	b->x1 = b->raw_x0 + b->size;
	b->y0 = b->raw_y0;
	if (b->x0 < 0) 
		b->x0 = 0;
	if (b->x1 >= g->win.width) 
		b->x1 = g->win.width - 1;
	if (b->y0 < 0) 
		b->y0 = 0;
	if (b->y1 >= g->win.height) 
		b->y1 = g->win.height - 1;
	return (b->x0 < b->x1 && b->y0 < b->y1);
}

static void	sprite_draw_col(t_game *g, t_sprite *b, int x, t_image *tex)
{
	int				y;
	int				tx;
	int				ty;
	unsigned int	c;

	tx = (x - b->raw_x0) * tex->width / b->size;

	if (tx < 0) tx = 0;
	if (tx >= tex->width) tx = tex->width - 1;

	y = b->y0;
	while (y < b->y1)
	{
		ty = (y - b->raw_y0) * tex->height / b->size;

		if (ty < 0) ty = 0;
		if (ty >= tex->height) ty = tex->height - 1;

		c = sprite_tex_px(tex, tx, ty);

		if ((c & 0x00FFFFFF) != 0)
			((unsigned int *)g->win.frame_buffer.img_addr)
				[y * (g->win.frame_buffer.l_len >> 2) + x] = c;

		y++;
	}
}

void	sprite_draw(t_game *g, t_sprite *b, t_image *tex)
{
	int	x;

	if (!g || !b || !tex || !tex->img_addr || !g->ray.z_buffer)
		return ;
	x = b->x0;
	while (x < b->x1)
	{
		if (b->depth < g->ray.z_buffer[x])
			sprite_draw_col(g, b, x, tex);
		x++;
	}
}
