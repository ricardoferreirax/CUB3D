/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_apply_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:25:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 17:33:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../../srcs/render/render3D.h"
#include "player3D.h"

static void	player_snap_axis(double *pos, double pull, double eps)
{
	double	center;
	double	dist;

	center = (double)((int)(*pos)) + 0.5;
	dist = center - *pos;
	if (dist < 0.0)
		dist = -dist;
	if (dist <= eps)
		*pos = center;
	else if (*pos < center)
		*pos += pull;
	else
		*pos -= pull;
}

static void	player_snap_for_move(t_game *g, double dx, double dy)
{
	double	ax;
	double	ay;

	ax = dx;
	ay = dy;
	if (ax < 0.0)
		ax = -ax;
	if (ay < 0.0)
		ay = -ay;
	if (ax > ay)
		player_snap_axis(&g->player.pos.tile_pos.y,
			PLAYER_SPEED * 0.50, 0.03);
	else
		player_snap_axis(&g->player.pos.tile_pos.x,
			PLAYER_SPEED * 0.50, 0.03);
}

static void	move_player_position(t_game *g, double dx, double dy)
{
	if (!player_collect_pacdots(g)
		&& !player_collect_energizer(g))
	{
		g->player.pos.tile_pos.x += dx;
		g->player.pos.tile_pos.y += dy;
	}
}

void	apply_player_movement(t_game *g, double dx, double dy)
{
	if (g->mode == MODE_PACMAN)
		player_snap_for_move(g, dx, dy);
	player_collision(g);
	player_wrap_position(g);
	move_player_position(g, dx, dy);
	handle_ghost_touch(g);
	if (g->player.collected_dots >= g->pacdot_count
		+ g->energizer_count
		&& g->player.collected_dots)
		reset_game(g, 0);
}
