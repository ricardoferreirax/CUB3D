/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 23:25:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

int	sprite_project(t_game *g, double world_x, double world_y, t_sprite *sp)
{
	double	dx;
	double	dy;
	double	inv_det;
	double	tx;
	double	ty;

	if (!g || !sp)
		return (0);
	dx = get_sprite_wrap_offset_x(g, world_x, world_y);
	dy = world_y - g->player.pos_y;
	inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
			- g->player.dir_x * g->player.plane_y);
	tx = inv_det * (g->player.dir_y * dx - g->player.dir_x * dy);
	ty = inv_det * (-g->player.plane_y * dx + g->player.plane_x * dy);
	if (ty <= 0.01)
		return (0);
	sp->depth = ty;
	sp->screen_x = (int)((g->win.width / 2.0) * (1.0 + tx / ty));
	return (1); }

int	sprite_build(t_game *g, t_sprite *b, int size_div)
{
	int	h;
	int	vmove;

	b->size = (int)((double)g->win.height / b->depth);
	if (b->size < 0)
		b->size = -b->size;
	b->size = b->size / size_div;
	if (b->size < 2)
		return (0);
	h = g->win.height / 2;
	vmove = (int)(0.10 * (double)g->win.height / b->depth);
	b->raw_x0 = b->screen_x - b->size / 2;
	b->raw_y0 = h - b->size / 2 + vmove;
	b->x0 = clampi(b->raw_x0, 0, g->win.width - 1);
	b->x1 = clampi(b->raw_x0 + b->size, 0, g->win.width - 1);
	b->y0 = clampi(b->raw_y0, 0, g->win.height - 1);
	b->y1 = clampi(b->raw_y0 + b->size, 0, g->win.height - 1);
	return (b->x0 < b->x1 && b->y0 < b->y1);
}

void	sprite_draw(t_game *g, t_sprite *b, t_image *tex)
{
	int	x;

	if (!g || !b || !tex || !tex->img_addr)
		return ;
	if (!g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	x = b->x0;
	while (x < b->x1)
	{
		if (b->depth < g->ray.z_buffer[x])
			sprite_draw_col(g, b, x, tex);
		x++;
	}
}
