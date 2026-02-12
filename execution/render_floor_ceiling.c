/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:16:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/12 09:53:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	draw_floor_ceiling_tile(t_image *dst, t_image *src, int y0, int y1)
{
	int	x;
	int	y;
	int	tx;
	int	ty;

	y = y0;
	while (y < y1)
	{
		x = 0;
		while (x < dst->width)
		{
			tx = x % src->width;
			ty = y % src->height;
			put_pixel_fast(dst, x, y, (int)tex_pixel(src, tx, ty));
			x++;
		}
		y++;
	}
}

void	render_ceiling(t_game *g)
{
	int	mid;

	mid = g->win.height / 2;
	if (g->tex.ceiling_img.img_ptr)
		draw_floor_ceiling_tile(&g->win.frame_buffer, &g->tex.ceiling_img, 0, mid);
	else
		fill_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
}

void	render_floor(t_game *g)
{
	int	mid;

	mid = g->win.height / 2;
	if (g->tex.floor_img.img_ptr)
		draw_floor_ceiling_tile(&g->win.frame_buffer, &g->tex.floor_img, mid, g->win.height);
	else
		fill_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
}
