/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pick_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:13:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 21:21:51 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

unsigned int	tex_pixel(t_image *tex, int x, int y)
{
	int				stride;
	unsigned int	*data;

	stride = tex->l_len / 4;
	if (!tex->img_addr)
		return (128);
	data = (unsigned int *)tex->img_addr;
	return (data[y * stride + x]);
}

t_image	*texture_pick_wall(t_game *g)
{
	if (g->ray.hit_tile == GATE)
		return (&g->tex.gate_close_img);
	if (g->ray.hit_side == 0)
	{
		if (g->ray.ray_dir_x > 0)
			return (&g->tex.ea_img);
		return (&g->tex.we_img);
	}
	if (g->ray.ray_dir_y > 0)
		return (&g->tex.so_img);
	return (&g->tex.no_img);
}
