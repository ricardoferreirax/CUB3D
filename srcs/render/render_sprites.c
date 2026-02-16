/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 05:05:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	render_pacdots(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return ;
	if (!g->pacdot_img.img_addr || !g->ray.z_buffer)
		return ;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active
			&& sprite_project(g, g->pacdots[i].x, g->pacdots[i].y, &box)
			&& sprite_build(g, &box, 6))
			sprite_draw(g, &box, &g->pacdot_img);
		i++;
	}
}


