/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:20:26 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:22:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

static void	ceiling_row_setup(t_game *g, t_fc *fc, int y)
{
	double	p;
	double	mid;
	double	r0x;
	double	r0y;

	mid = 0.5 * (double)g->win.height + CEILING_HORIZON;
	p = mid - (double)y;
	if (p < CEILING_P_MIN)
		p = CEILING_P_MIN;
	fc->rowdist = (0.5 * (double)g->win.height * CEILING_DIST) / p;
	r0x = g->player.dir_x - g->player.plane_x;
	r0y = g->player.dir_y - g->player.plane_y;
	fc->stepx = fc->rowdist * ((g->player.dir_x + g->player.plane_x) - r0x)
		/ (double)g->win.width;
	fc->stepy = fc->rowdist * ((g->player.dir_y + g->player.plane_y) - r0y)
		/ (double)g->win.width;
	fc->fx = g->player.pos_x + fc->rowdist * r0x;
	fc->fy = g->player.pos_y + fc->rowdist * r0y;
}

static void	ceiling_draw_row(t_game *g, t_fc *fc, t_image *tex, int y)
{
	unsigned int	*row;
	int				x;
	int				tx;
	int				ty;

	row = (unsigned int *)(g->win.frame_buffer.img_addr + y
			* g->win.frame_buffer.l_len);
	x = 0;
	while (x < g->win.width)
	{
		convert_texture_coords(fc, tex, &tx, &ty);
		row[x] = tex_pixel(tex, tx, ty);
		fc->fx += fc->stepx;
		fc->fy += fc->stepy;
		x++;
	}
}

void	render_ceiling_texture(t_game *g)
{
	t_fc	fc;
	int		y;
	int		mid;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.ceiling_img.img_ptr)
	{
		fill_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
		return ;
	}
	mid = g->win.height / 2;
	y = 0;
	while (y < mid - 2)
	{
		ceiling_row_setup(g, &fc, y);
		ceiling_draw_row(g, &fc, &g->tex.ceiling_img, y);
		y++;
	}
}
