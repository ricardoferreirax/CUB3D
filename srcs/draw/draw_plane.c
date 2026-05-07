/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:03:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 18:06:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "draw.h"

void	set_plane(t_game *g, t_fc *plane, double dist)
{
	plane->dist = dist;
	plane->step_x = dist * (2.0 * g->player.plane.x) / g->win.width;
	plane->step_y = dist * (2.0 * g->player.plane.y) / g->win.width;
	plane->pos_x = g->player.pos.tile_pos.x + dist 
		* (g->player.dir.x - g->player.plane.x);
	plane->pos_y = g->player.pos.tile_pos.y + dist 
		* (g->player.dir.y - g->player.plane.y);
}

static int	get_tex_coord(double pos, int size)
{
	int	coord;

	coord = (int)(pos * size) % size;
	if (coord < 0)
		coord += size;
	return (coord);
}

void	draw_plane_row(t_game *g, t_fc *plane, t_image *tex, int row)
{
	unsigned int	*pixels;
	int				col;
	int				tex_x;
	int				tex_y;
	int				stride;

	pixels = (unsigned int *)(g->win.frame_buffer.img_addr + row 
			* g->win.frame_buffer.l_len);
	col = 0;
	if (!tex || !tex->img_addr)
	{
		while (col < g->win.width)
			pixels[col++] = 128;
		return ;
	}
	tex->data = (unsigned int *)tex->img_addr;
	stride = tex->l_len / 4;
	while (col < g->win.width)
	{
		tex_x = get_tex_coord(plane->pos_x, tex->width);
		tex_y = get_tex_coord(plane->pos_y, tex->height);
		pixels[col++] = tex->data[tex_y * stride + tex_x];
		plane->pos_x += plane->step_x;
		plane->pos_y += plane->step_y;
	}
}
