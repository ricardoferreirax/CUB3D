/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:46:55 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:48:57 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	ft_pixel_put(t_image *s, int x, int y, unsigned int color)
{
	char	*dest;

	dest = s->img_addr + (y * s->l_len + x * (s->bpp / 8));
	*(unsigned int *)dest = color;
}

int	pixeL_get_coord(t_sprite_sheet *sheet, int i, int x, int y)
{
	char	*dest;

	dest = sheet->sprite_img.img_addr + ((sheet->sprites[i].coord.y + y)
			* sheet->sprite_img.l_len + (sheet->sprites[i].coord.x + x)
			* (sheet->sprite_img.bpp / 8));
	return (*(unsigned int *)dest);
}

int	pixel_get(t_image *data, int x, int y)
{
	char	*dest;

	dest = data->img_addr + (y * data->l_len + x * (data->bpp / 8));
	return (*(unsigned int *)dest);
}
