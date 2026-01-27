/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:25:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/27 20:51:54 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

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
