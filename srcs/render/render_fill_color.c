/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fill_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:40:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/15 19:40:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	fill_row_fast(t_image *img, int y, int color)
{
	unsigned int	*row;
	int				stride;
	int				x;

	stride = img->l_len / 4;
	row = (unsigned int *)img->img_addr + (y * stride);
	x = 0;
	while (x < img->width)
		row[x++] = (unsigned int)color;
}

void	fill_ceiling_color(t_image *img, int color, int horizon)
{
	int	y;
	int	end;

	if (!img || !img->img_addr)
		return ;
	end = img->height / 2 - horizon;
	if (end < 0) 
		end = 0;
	if (end > img->height) 
		end = img->height;
	y = 0;
	while (y < end)
		fill_row_fast(img, y++, color);
}

void	fill_floor_color(t_image *img, int color, int horizon)
{
	int	y;
	int	start;

	if (!img || !img->img_addr)
		return ;
	start = img->height / 2 - horizon;
	if (start < 0) 
		start = 0;
	if (start > img->height) 
		start = img->height;
	y = start;
	while (y < img->height)
		fill_row_fast(img, y++, color);
}
