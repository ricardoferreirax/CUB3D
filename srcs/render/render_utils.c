/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:18:28 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 17:48:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

// void	put_pixel(t_image *img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (!img || !img->img_addr)
// 		return ;
// 	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
// 		return ;
// 	dst = img->img_addr + (y * img->l_len) + (x * (img->bpp / 8));
// 	*(unsigned int *)dst = (unsigned int)color;
// }

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
		i -= 1;           /* isto faz o "floor" só para negativos */
	return (x - (double)i);
}

void	convert_texture_coords(t_fc *fc, t_image *tex, int *tx, int *ty)
{
	double	u;
	double	v;

	u = fract_pos(fc->fx);
	v = fract_pos(fc->fy);
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
