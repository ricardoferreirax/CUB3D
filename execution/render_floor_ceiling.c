/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:16:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/13 10:49:39 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

// prepara os valores para desenhar uma linha y (row) com perspetiva
static int	fc_row_setup(t_game *g, t_fc *fc, int y, int is_ceil)
{
	double	p;
	double	mid;
	double	r0x;
	double	r0y;

	mid = 0.5 * g->win.height;
	if (is_ceil)
		p = mid - (double)y;
	else
		p = (double)y - mid;
	if (p == 0.0)
		return (0);
	fc->rowdist = (0.5 * g->win.height) / p;
	r0x = g->player.dir_x - g->player.plane_x;
	r0y = g->player.dir_y - g->player.plane_y;
	fc->stepx = fc->rowdist * ((g->player.dir_x + g->player.plane_x) - r0x) / (double)g->win.width;
	fc->stepy = fc->rowdist * ((g->player.dir_y + g->player.plane_y) - r0y) / (double)g->win.width;
	fc->fx = g->player.pos_x + fc->rowdist * r0x;
	fc->fy = g->player.pos_y + fc->rowdist * r0y;
	return (1);
}

// desenha a linha y inteira (x = 0..width-1) a partir de fc->fx/fy + steps para cada pixel
static void	fc_draw_row(t_game *g, t_fc *fc, t_image *tex, int y)
{
	int	x;
	int	tx;
	int	ty;

	x = 0;
	while (x < g->win.width)
	{
		tx = (int)((fc->fx - (double)((int)fc->fx)) * (double)tex->width);
		ty = (int)((fc->fy - (double)((int)fc->fy)) * (double)tex->height);
		if (tx < 0) 
			tx = 0;
		if (ty < 0) 
			ty = 0;
		if (tx >= tex->width) 
			tx = tex->width - 1;
		if (ty >= tex->height) 
			ty = tex->height - 1;
		put_pixel_fast(&g->win.frame_buffer, x, y, (int)tex_pixel(tex, tx, ty));
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
	y = mid;
	while (y < g->win.height)
	{
		if (fc_row_setup(g, &fc, y, 0))
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
	while (y < mid)
	{
		if (fc_row_setup(g, &fc, y, 1))
			fc_draw_row(g, &fc, &g->tex.ceiling_img, y);
		y++;
	}
}
