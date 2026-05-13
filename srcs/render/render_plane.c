/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 18:29:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../draw/draw.h"
#include "render3D.h"

static double	get_floor_dist(t_game *g, int row)
{
	double	screen_dist;

	screen_dist = row - g->win.height * 0.5;
	if (screen_dist < FLOOR_MIN_DIST)
		screen_dist = FLOOR_MIN_DIST;
	return ((g->win.height * 0.5) / screen_dist);
}

static double	get_ceiling_dist(t_game *g, int row)
{
	double	screen_dist;

	screen_dist = (g->win.height * 0.5 + CEILING_HORIZON) - row;
	if (screen_dist < CEILING_MIN_SCREEN_DIST)
		screen_dist = CEILING_MIN_SCREEN_DIST;
	return ((g->win.height * 0.5 * CEILING_DIST) / screen_dist);
}

void	render_floor_texture(t_game *g)
{
	int		row;
	t_fc	plane;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.floor_img.img_ptr)
	{
		draw_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
		return ;
	}
	row = g->win.height / 2 + FLOOR_START_OFFSET;
	while (row < g->win.height)
	{
		set_plane(g, &plane, get_floor_dist(g, row));
		draw_plane_row(g, &plane, &g->tex.floor_img, row);
		row++;
	}
}

void	render_ceiling_texture(t_game *g)
{
	int		row;
	t_fc	plane;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.ceiling_img.img_ptr)
	{
		draw_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
		return ;
	}
	row = 0;
	while (row < g->win.height / 2 - CEILING_CENTER_MARGIN)
	{
		set_plane(g, &plane, get_ceiling_dist(g, row));
		draw_plane_row(g, &plane, &g->tex.ceiling_img, row);
		row++;
	}
}
