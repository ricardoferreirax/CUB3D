/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:09:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/27 21:31:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	draw_pacdots(t_game *g)
{
	t_sprite	box;
	int			i;
	double		wx;
	double		wy;

	if (!g || !g->pacdots || !g->tex.pacdot_img.img_addr)
		return ;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active)
		{
			wx = g->pacdots[i].x * (double)TILE_SIZE;
			wy = g->pacdots[i].y * (double)TILE_SIZE;
			if (sprite_project(g, wx, wy, &box))
			{
				if (sprite_build(g, &box, 6))
					sprite_draw(g, &box, &g->tex.pacdot_img);
			}
		}
		i++;
	}
}

static void	draw_energizers(t_game *g)
{
	t_sprite	box;
	int			i;
	double		wx;
	double		wy;

	if (!g || !g->energizers || !g->tex.energizer_img.img_addr)
		return ;
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active)
		{
			wx = g->energizers[i].x * (double)TILE_SIZE;
			wy = g->energizers[i].y * (double)TILE_SIZE;
			if (sprite_project(g, wx, wy, &box))
			{
				if (sprite_build(g, &box, 3))
					sprite_draw(g, &box, &g->tex.energizer_img);
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
			wx = ((double)g->ghosts[i].pos.tile_pos.x + 0.5) * (double)TILE_SIZE;
			wy = ((double)g->ghosts[i].pos.tile_pos.y + 0.5) * (double)TILE_SIZE;
			if (sprite_project(g, wx, wy, &box))
			{
				if (sprite_build(g, &box, 2))
					sprite_draw(g, &box, tex);
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
