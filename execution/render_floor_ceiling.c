/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:16:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/13 12:17:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	fc_row_setup(t_game *g, t_fc *fc, int y, int is_ceil)
{
	double	p;
	double	mid;
	double	r0x;
	double	r0y;

	mid = 0.5 * (double)g->win.height;
	if (is_ceil)
		p = mid - (double)y;
	else
		p = (double)y - mid;
	if (p < 4.0 && p > -4.0)
	{
    	if (p < 0.0) 
			p = -4.0;
    	else 
			p = 4.0;
	}
	fc->rowdist = (0.5 * (double)g->win.height) / p;
	r0x = g->player.dir_x - g->player.plane_x;
	r0y = g->player.dir_y - g->player.plane_y;
	fc->stepx = fc->rowdist * ((g->player.dir_x + g->player.plane_x) - r0x) / (double)g->win.width;
	fc->stepy = fc->rowdist * ((g->player.dir_y + g->player.plane_y) - r0y) / (double)g->win.width;
	fc->fx = g->player.pos_x + fc->rowdist * r0x;
	fc->fy = g->player.pos_y + fc->rowdist * r0y;
}

static void	fc_get_tex_coords(t_fc *fc, t_image *tex, int *tx, int *ty)
{
	double	u;
	double	v;

	u = fc->fx - floor(fc->fx);
	v = fc->fy - floor(fc->fy);
	*tx = (int)(u * (double)tex->width);
	*ty = (int)(v * (double)tex->height);
	if (*tx < 0)
		*tx = 0;
	if (*ty < 0)
		*ty = 0;
	if (*tx >= tex->width)
		*tx = tex->width - 1;
	if (*ty >= tex->height)
		*ty = tex->height - 1;
}

static void	fc_draw_row(t_game *g, t_fc *fc, t_image *tex, int y)
{
	unsigned int	*row;
	int				x;
	int				tx;
	int				ty;

	row = (unsigned int *)(g->win.frame_buffer.img_addr + y * g->win.frame_buffer.l_len);
	x = 0;
	while (x < g->win.width)
	{
		fc_get_tex_coords(fc, tex, &tx, &ty);
		row[x] = tex_pixel(tex, tx, ty);
		fc->fx += fc->stepx;
		fc->fy += fc->stepy;
		x++;
	}
}

void	render_floor(t_game *g)
{
	t_fc	fc;
	int		y;
	int		mid;

	if (!g->tex.floor_img.img_ptr)
	{
		fill_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
		return ;
	}
	mid = g->win.height / 2;
	y = mid + 2;
	while (y < g->win.height)
	{
		fc_row_setup(g, &fc, y, 0);
		fc_draw_row(g, &fc, &g->tex.floor_img, y);
		y++;
	}
}

void	render_ceiling(t_game *g)
{
	t_fc	fc;
	int		y;
	int		mid;

	if (!g->tex.ceiling_img.img_ptr)
	{
		fill_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
		return ;
	}
	mid = g->win.height / 2;
	y = 0;
	while (y < mid - 2)
	{
		fc_row_setup(g, &fc, y, 1);
		fc_draw_row(g, &fc, &g->tex.ceiling_img, y);
		y++;
	}
}
