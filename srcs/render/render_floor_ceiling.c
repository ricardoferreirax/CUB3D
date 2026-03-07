/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/07 22:19:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	setup_plane_row(t_game *g, t_fc *plane, double dist)
{
	double	start_dir_x;
	double	start_dir_y;

	start_dir_x = g->player.dir_x - g->player.plane_x;
	start_dir_y = g->player.dir_y - g->player.plane_y;
	plane->dist = dist;
	plane->step_x = dist * (2.0 * g->player.plane_x) / g->win.width;
	plane->step_y = dist * (2.0 * g->player.plane_y) / g->win.width;
	plane->pos_x = g->player.pos_x + dist * start_dir_x;
	plane->pos_y = g->player.pos_y + dist * start_dir_y;
}

static void	convert_texture_coords(t_fc *fc, t_image *tex, int *tex_x, int *tex_y)
{
	double	u;
	double	v;

	u = fract_pos(fc->pos_x);
	v = fract_pos(fc->pos_y);
	*tex_x = (int)(u * (double)tex->width);
	*tex_y = (int)(v * (double)tex->height);
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_x >= tex->width)
		*tex_x = tex->width - 1;
	if (*tex_y >= tex->height)
		*tex_y = tex->height - 1;
}

static void	draw_plane_row(t_game *g, t_fc *plane, t_image *tex, int row)
{
	unsigned int	*pixels;
	int				col;
	int				tex_x;
	int				tex_y;

	pixels = (unsigned int *)(g->win.frame_buffer.img_addr
			+ row * g->win.frame_buffer.l_len);
	col = 0;
	while (col < g->win.width)
	{
		convert_texture_coords(plane, tex, &tex_x, &tex_y);
		pixels[col] = tex_pixel(tex, tex_x, tex_y);
		plane->pos_x += plane->step_x;
		plane->pos_y += plane->step_y;
		col++;
	}
}

void	render_floor_texture(t_game *g)
{
	t_fc	plane;
	int		row;
	double	dist;
	double	screen_dist;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.floor_img.img_ptr)
	{
		fill_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
		return ;
	}
	row = g->win.height / 2 + FLOOR_START_OFFSET;
	while (row < g->win.height)
	{
		screen_dist = row - g->win.height * 0.5;
		if (screen_dist < FLOOR_MIN_DIST)
			screen_dist = FLOOR_MIN_DIST;
		dist = (g->win.height * 0.5) / screen_dist;
		setup_plane_row(g, &plane, dist);
		draw_plane_row(g, &plane, &g->tex.floor_img, row);
		row++;
	}
}

void	render_ceiling_texture(t_game *g)
{
	t_fc	plane;
	int		row;
	double	screen_dist;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.ceiling_img.img_ptr)
	{
		fill_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
		return ;
	}
	row = 0;
	while (row < (g->win.height / 2) - CEILING_CENTER_MARGIN)
	{
		screen_dist = (g->win.height * 0.5 + CEILING_HORIZON) - row;
		if (screen_dist < CEILING_MIN_SCREEN_DIST)
			screen_dist = CEILING_MIN_SCREEN_DIST;
		setup_plane_row(g, &plane,
			(g->win.height * 0.5 * CEILING_DIST) / screen_dist);
		draw_plane_row(g, &plane, &g->tex.ceiling_img, row);
		row++;
	}
}
