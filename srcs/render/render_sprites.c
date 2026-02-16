/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:06:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 22:55:05 by rmedeiro         ###   ########.fr       */
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

void	render_energizers(t_game *g)
{
	t_sprite	box;
	int			i;

	if (!g || !g->energizers || g->energizer_count <= 0)
		return ;
	if (!g->energizer_img.img_addr || !g->ray.z_buffer)
		return ;
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active
			&& sprite_project(g, g->energizers[i].x, g->energizers[i].y, &box)
			&& sprite_build(g, &box, 3))
			sprite_draw(g, &box, &g->energizer_img);
		i++;
	}
}

static void	render_one_ghost(t_game *g, t_ghost *gh)
{
	t_sprite	box;
	t_image		*tex;

	tex = ghost_tex(g, gh);
	if (!tex || !tex->img_addr)
		return ;
	if (!sprite_project(g, gh->sprite_x, gh->sprite_y, &box))
		return ;
	if (!sprite_build(g, &box, 2))
		return ;
	sprite_draw(g, &box, tex);
}

void	render_ghosts(t_game *g)
{
	int	i;

	if (!g || !g->ray.z_buffer)
		return ;
	i = 0;
	while (i < 4)
	{
		render_one_ghost(g, &g->ghosts[i]);
		i++;
	}
}
