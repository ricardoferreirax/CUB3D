/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pick_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:13:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 22:06:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

unsigned int	tex_pixel(t_image *tex, int x, int y)
{
	unsigned int	*data;
	int				stride;

	stride = tex->l_len / 4;
	data = (unsigned int *)tex->img_addr;
	return (data[y * stride + x]);
}

t_image *texture_pick_wall(t_game *g)
{
    if (g->ray.hit_tile == GATE)
    {
        if (g->gate_passable)
            return (&g->tex.gate_open_img);
        return (&g->tex.gate_close_img);
    }
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
