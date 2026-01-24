/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:02:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/24 20:28:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

// void	put_pixel(t_image *img, int x, int y, int color)
// {
// 	char	*dst;
// 	int		bytes_per_pixel;

// 	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
// 		return ;
// 	bytes_per_pixel = img->bpp / 8;
// 	dst = img->img_addr + (y * img->l_len + x * bytes_per_pixel);
// 	*(unsigned int *)dst = (unsigned int)color;
// }

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	*buf;
	int	stride;

	if (!img || !img->img_addr)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	buf = (int *)img->img_addr;
	stride = img->l_len / 4;
	buf[y * stride + x] = color;
}
