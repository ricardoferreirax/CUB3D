/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:18:28 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/07 22:18:19 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	put_pixel_fast(t_image *img, int x, int y, int color)
{
	unsigned int	*buf;
	int				stride;

	if (!img || !img->img_addr)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	stride = img->l_len / 4;
	buf = (unsigned int *)img->img_addr;
	buf[y * stride + x] = (unsigned int)color;
}

double	fract_pos(double x)
{
	int	i;

	i = (int)x;
	if (x < 0.0 && (double)i != x)
		i -= 1;
	return (x - (double)i);
}

t_image	*ghost_tex(t_game *g, t_ghost *gh)
{
	if (!g || !gh)
		return (NULL);
	if (gh->name == BLINKY)
		return (&g->tex.blinky_img);
	if (gh->name == PINKY)
		return (&g->tex.pinky_img);
	if (gh->name == INKY)
		return (&g->tex.inky_img);
	return (&g->tex.clyde_img);
}

int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}
