/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:09:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 21:57:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static void	draw_pacdots(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->pacdots || !g->pacdot_img.img_addr)
		return ;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active)
		{
			if (sprite_project(g, g->pacdots[i].x, g->pacdots[i].y, &box))
			{
				if (sprite_build(g, &box, 6))
					sprite_draw(g, &box, &g->pacdot_img);
			}
		}
		i++;
	}
}

static void	draw_energizers(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->energizers || !g->energizer_img.img_addr)
		return ;
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active)
		{
			if (sprite_project(g, g->energizers[i].x, g->energizers[i].y, &box))
			{
				if (sprite_build(g, &box, 3))
					sprite_draw(g, &box, &g->energizer_img);
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

	if (!g)
		return ;
	i = 0;
	while (i < 4)
	{
		tex = ghost_tex(g, &g->ghosts[i]);
		if (tex && tex->img_addr)
		{
			if (sprite_project(g, g->ghosts[i].sprite_x, g->ghosts[i].sprite_y, &box))
			{
				if (sprite_build(g, &box, 2))
					sprite_draw(g, &box, tex);
			}
		}
		i++;
	}
}

static void	draw_open_gates(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->gates || !g->tex.gate_open_img.img_addr)
		return ;
	if (!g->gate_passable)
		return ;
	i = 0;
	while (i < g->gate_count)
	{
		if (g->gates[i].active)
		{
			if (sprite_project(g, g->gates[i].x, g->gates[i].y, &box))
			{
				if (sprite_build(g, &box, 1))
					sprite_draw(g, &box, &g->tex.gate_open_img);
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
	draw_open_gates(g);
}
