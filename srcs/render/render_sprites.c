/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:09:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 17:19:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	draw_pacdots(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->pacdots || !g->tex.pacdot_img.img_addr)
		return ;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active)
		{
			if (sprite_project(g, g->pacdots[i].pos.tile_pos.x,
					g->pacdots[i].pos.tile_pos.y, &box))
			{
				if (build_sprite_box(g, &box, 6))
					draw_sprite(g, &box, &g->tex.pacdot_img);
			}
		}
		i++;
	}
}

static void	draw_energizers(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->energizers || !g->tex.energizer_img.img_addr)
		return ;
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active)
		{
			if (sprite_project(g, g->energizers[i].pos.tile_pos.x,
					g->energizers[i].pos.tile_pos.y, &box))
			{
				if (build_sprite_box(g, &box, 3))
					draw_sprite(g, &box, &g->tex.energizer_img);
			}
		}
		i++;
	}
}

static void	draw_ghosts(t_game *g)
{
	t_sprite	box;
	t_image		*tex;
	int			i;
	double		wx;
	double		wy;

	if (!g)
		return ;
	i = 0;
	while (i < 4)
	{
		tex = ghost_tex(g, &g->ghosts[i]);
		if (tex && tex->img_addr)
		{
			wx = g->ghosts[i].pos.tile_pos.x;
			wy = g->ghosts[i].pos.tile_pos.y;
			if (sprite_project(g, wx, wy, &box))
			{
				if (build_sprite_box(g, &box, 2))
					draw_sprite(g, &box, tex);
			}
		}
		i++;
	}
}

void	render_all_sprites(t_game *g)
{
	if (!g || !g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	draw_pacdots(g);
	draw_energizers(g);
	draw_ghosts(g);
}
