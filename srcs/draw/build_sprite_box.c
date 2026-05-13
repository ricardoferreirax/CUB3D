/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_sprite_box.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 16:27:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "draw.h"

int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp)
{
	double	det;
	double	camera_x;

	if (!g || !sp)
		return (0);
	sp->cam_x = get_sprite_wrap_offset_x(g, wx, wy);
	sp->cam_y = wy - g->player.pos.tile_pos.y;
	det = g->player.plane.x * g->player.dir.y
		- g->player.dir.x * g->player.plane.y;
	sp->dist = (-g->player.plane.y * sp->cam_x
			+ g->player.plane.x * sp->cam_y) / det;
	if (sp->dist <= 0.01)
		return (0);
	camera_x = (g->player.dir.y * sp->cam_x - g->player.dir.x 
				* sp->cam_y) / (det * sp->dist);
	sp->screen_x = (g->win.width / 2) * (1 + camera_x);
	return (1);
}

int	build_sprite_box(t_game *g, t_sprite *sp, int scale)
{
	int	half;

	if (!g || !sp || scale <= 0 || sp->dist <= 0.01)
		return (0);
	sp->size = (int)(g->win.height / sp->dist) / scale;
	if (sp->size < 2)
		return (0);
	half = sp->size / 2;
	sp->tex_start_x = sp->screen_x - half;
	sp->tex_start_y = g->win.height / 2 - half;
	sp->tex_start_y += (int)(g->win.height * 0.10 / sp->dist);
	sp->draw_start_x = clamp_int(sp->tex_start_x, 0, g->win.width - 1);
	sp->draw_end_x = clamp_int(sp->tex_start_x + sp->size, 0, g->win.width - 1);
	sp->draw_start_y = clamp_int(sp->tex_start_y, 0, g->win.height - 1);
	sp->draw_end_y = clamp_int(sp->tex_start_y + sp->size, 0, g->win.height - 1);
	return (sp->draw_start_x < sp->draw_end_x && sp->draw_start_y < sp->draw_end_y);
}
