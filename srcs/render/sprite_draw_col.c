/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:11:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/09 16:45:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static unsigned int	sprite_tex_px(t_image *tex, int x, int y)
{
	int	stride;

	if (!tex || !tex->img_addr)
		return (0);
	stride = tex->l_len >> 2;
	return (((unsigned int *)tex->img_addr)[y * stride + x]);
}

static int	sprite_tex_coord(int screen_pos, int sprite_start,
			int tex_size, int sprite_size)
{
	int	tex_pos;

	tex_pos = (screen_pos - sprite_start) * tex_size / sprite_size;
	return (clamp_int(tex_pos, 0, tex_size - 1));
}

int	sprite_draw_col(t_game *g, t_sprite *sp, int col, t_image *tex)
{
	int				row;
	int				tex_x;
	int				pixel_idx;
	unsigned int	color;

	tex_x = sprite_tex_coord(col, sp->tex_start_x, tex->width, sp->size);
	row = sp->draw_start_y;
	while (++row < sp->draw_end_y)
	{
		pixel_idx = row * g->win.width + col;
		if (sp->dist < g->ray.sprite_z[pixel_idx])
		{
			color = sprite_tex_px(tex, tex_x,
					sprite_tex_coord(row, sp->tex_start_y,
						tex->height, sp->size));
			if ((color & 0x00FFFFFF) != 0)
			{
				((unsigned int *)g->win.frame_buffer.img_addr)
					[row * (g->win.frame_buffer.l_len >> 2) + col] = color;
				g->ray.sprite_z[pixel_idx] = sp->dist;
			}
		}
	}
	return (1);
}
