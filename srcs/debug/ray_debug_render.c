/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:47:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:47:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	render_raycast_debug(t_game *g)
{
	t_raycasting	ray;
	t_point			start;
	int				col;

	if (!g)
		return ;
	debug_draw_map(g);
	start = debug_world_to_screen(g->player.pos.tile_pos.x,
			g->player.pos.tile_pos.y);
	col = 0;
	while (col < g->win.width)
	{
		if (debug_cast_screen_ray(g, col, &ray))
			debug_draw_casted_ray(g, start, ray);
		col += DEBUG_RAY_STEP;
	}
	debug_draw_player_marker(g, start);
}