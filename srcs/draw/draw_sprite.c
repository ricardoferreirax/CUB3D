/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 15:29:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "draw.h"

int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp)
{
	double	dx;
	double	dy;
	double	cam_inv_det;
	double	depth;

	if (!g || !sp)
		return (0);
	dx = get_sprite_wrap_offset_x(g, wx, wy);
	dy = wy - g->player.pos.tile_pos.y;
	cam_inv_det = 1.0 / (g->player.plane.x * g->player.dir.y - g->player.dir.x
			* g->player.plane.y);
	depth = cam_inv_det * (-g->player.plane.y * dx + g->player.plane.x * dy);
	if (depth <= 0.01)
		return (0);
	sp->dist = depth;
	sp->screen_x = (int)(g->win.width * 0.5 * (1.0 + (cam_inv_det
					* (g->player.dir.y * dx - g->player.dir.x * dy)) / depth));
	return (1);
}

int	build_sprite_box(t_game *g, t_sprite *sp, int scale_div)
{
	int	offset_y;
	int	size;
	int	center_y;

	size = (int)((double)g->win.height / sp->dist);
	if (size < 0)
		size = -size;
	size /= scale_div;
	if (size < 2)
		return (0);
	center_y = g->win.height / 2;
	offset_y = (int)(0.10 * g->win.height / sp->dist);
	sp->size = size;
	sp->tex_start_x = sp->screen_x - size / 2;
	sp->tex_start_y = center_y - size / 2 + offset_y;
	sp->draw_start_x = clamp_int(sp->tex_start_x, 0, g->win.width - 1);
	sp->draw_end_x = clamp_int(sp->tex_start_x + size, 0, g->win.width - 1);
	sp->draw_start_y = clamp_int(sp->tex_start_y, 0, g->win.height - 1);
	sp->draw_end_y = clamp_int(sp->tex_start_y + size, 0, g->win.height - 1);
	return (sp->draw_start_x < sp->draw_end_x
		&& sp->draw_start_y < sp->draw_end_y);
}

void	draw_sprite(t_game *g, t_sprite *sp, t_image *tex)
{
	double	*zbuf;
	int		col;

	if (!g || !sp || !tex || !tex->img_addr)
		return ;
	if (!g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	zbuf = g->ray.z_buffer;
	col = sp->draw_start_x;
	while (col < sp->draw_end_x)
	{
		if (sp->dist < zbuf[col])
			draw_sprite_column(g, sp, col, tex);
		col++;
	}
}
