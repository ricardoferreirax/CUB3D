/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/15 21:25:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	floor_row_setup(t_game *g, t_fc *fc, int y)
{
	double	p;
	double	mid;
	double	r0x;
	double	r0y;

	mid = 0.5 * (double)g->win.height;
	p = (double)y - mid;
	if (p < 4.0)
		p = 4.0;
	fc->rowdist = (0.5 * (double)g->win.height) / p;
	r0x = g->player.dir.x - g->player.plane.x;
	r0y = g->player.dir.y - g->player.plane.y;
	fc->stepx = fc->rowdist * ((g->player.dir.x + g->player.plane.x) - r0x)
		/ (double)g->win.width;
	fc->stepy = fc->rowdist * ((g->player.dir.y + g->player.plane.y) - r0y)
		/ (double)g->win.width;
	fc->fx = g->player.pos.tile_pos.x + fc->rowdist * r0x;
	fc->fy = g->player.pos.tile_pos.y + fc->rowdist * r0y;
}

static void	floor_draw_row(t_game *g, t_fc *fc, t_image *tex, int y)
{
	unsigned int	*row;
	int				x;
	int				tx;
	int				ty;

	row = (unsigned int *)(g->win.frame_buffer.img_addr
			+ y * g->win.frame_buffer.l_len);
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

void	render_floor_texture(t_game *g)
{
	t_fc	fc;
	int		y;
	int		mid;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.floor_img.img_ptr)
	{
    	fill_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
    	return ;
	}
	mid = g->win.height / 2;
	y = mid + 2;
	while (y < g->win.height)
	{
		floor_row_setup(g, &fc, y);
		floor_draw_row(g, &fc, &g->tex.floor_img, y);
		y++;
	}
}
