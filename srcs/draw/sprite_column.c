/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:11:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 16:28:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "draw.h"

static unsigned int	get_sprite_color(t_sprite *sp,
							t_image *tex, int col, int row)
{
	unsigned int	*data;
	int				tex_x;
	int				tex_y;

	data = (unsigned int *)tex->img_addr;
	tex_x = (col - sp->tex_start_x) * tex->width / sp->size;
	tex_y = (row - sp->tex_start_y) * tex->height / sp->size;
	tex_x = clamp_int(tex_x, 0, tex->width - 1);
	tex_y = clamp_int(tex_y, 0, tex->height - 1);
	return (data[tex_y * (tex->l_len / 4) + tex_x]);
}

int	draw_sprite_column(t_game *g, t_sprite *sp, int col, t_image *tex)
{
	unsigned int	color;
	int				row;
	int				idx;

	if (!g || !sp || !tex || !tex->img_addr)
		return (0);
	row = sp->draw_start_y;
	while (row < sp->draw_end_y)
	{
		idx = row * g->win.width + col;
		if (sp->dist < g->ray.sprite_z[idx])
		{
			color = get_sprite_color(sp, tex, col, row);
			if ((color & 0x00FFFFFF) != 0)
			{
				put_pixel_fast(&g->win.frame_buffer, col, row, color);
				g->ray.sprite_z[idx] = sp->dist;
			}
		}
		row++;
	}
	return (1);
}
