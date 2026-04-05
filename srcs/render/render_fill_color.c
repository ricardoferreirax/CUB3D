/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fill_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:40:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/07 22:38:33 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	fill_rows(t_image *img, int start, int end, int color)
{
	unsigned int	*pixels;
	int				row;
	int				col;
	int				stride;

	start = clamp_int(start, 0, img->height);
	end = clamp_int(end, 0, img->height);
	stride = img->l_len / 4;
	row = start;
	while (row < end)
	{
		pixels = (unsigned int *)img->img_addr + (row * stride);
		col = 0;
		while (col < img->width)
		{
			pixels[col] = (unsigned int)color;
			col++;
		}
		row++;
	}
}

void	fill_ceiling_color(t_image *img, int color, int horizon)
{
	int	end;

	if (!img || !img->img_addr)
		return ;
	end = img->height / 2 - horizon;
	fill_rows(img, 0, end, color);
}

void	fill_floor_color(t_image *img, int color, int horizon)
{
	int	start;

	if (!img || !img->img_addr)
		return ;
	start = img->height / 2 - horizon;
	fill_rows(img, start, img->height, color);
}
