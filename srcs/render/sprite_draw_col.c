/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:11:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/20 22:20:54 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static unsigned int	sprite_tex_px(t_image *t, int x, int y)
{
	int	s;

	if (!t || !t->img_addr)
		return (0);
	s = t->l_len >> 2;
	return (((unsigned int *)t->img_addr)[y * s + x]);
}

static int	sprite_tx(t_sprite *b, t_image *tex, int x)
{
	int	tx;

	tx = (x - b->raw_x0) * tex->width / b->size;
	return (clampi(tx, 0, tex->width - 1));
}

static int	sprite_ty(t_sprite *b, t_image *tex, int y)
{
	int	ty;

	ty = (y - b->raw_y0) * tex->height / b->size;
	return (clampi(ty, 0, tex->height - 1));
}

int	sprite_draw_col(t_game *g, t_sprite *b, int x, t_image *tex)
{
	int				y;
	int				tx;
	unsigned int	c;
	int				drawn;

	drawn = 0;
	tx = sprite_tx(b, tex, x);
	y = b->y0;
	while (y < b->y1)
	{
		c = sprite_tex_px(tex, tx, sprite_ty(b, tex, y));
		if ((c & 0x00FFFFFF) != 0)
		{
			((unsigned int *)g->win.frame_buffer.img_addr)
				[y * (g->win.frame_buffer.l_len >> 2) + x] = c;
			drawn = 1;
		}
		y++;
	}
	return (drawn);
}
