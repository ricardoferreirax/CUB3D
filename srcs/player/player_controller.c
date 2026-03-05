/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 21:34:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	apply_player_movement(t_game *g, double dx, double dy)
{
	g->player.pos_x += dx;
	g->player.pos_y += dy;
	player_collision(g);
	player_wrap_position(g);
	player_collect_pacdots(g);
}

static void	player_rotate(t_game *g, double angle)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	prev_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos_a - g->player.dir_y * sin_a;
	g->player.dir_y = prev_dir_x * sin_a + g->player.dir_y * cos_a;
	prev_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos_a - g->player.plane_y * sin_a;
	g->player.plane_y = prev_plane_x * sin_a + g->player.plane_y * cos_a;
}

static void	player_apply_action(t_game *g, t_player_action act)
{
	double	dx;
	double	dy;

	dx = 0.0;
	dy = 0.0;
	if (act == ROTATE_RIGHT)
		player_rotate(g, ROT_SPEED);
	else if (act == ROTATE_LEFT)
		player_rotate(g, -ROT_SPEED);
	else
	{
		if (act == MOVE_FORWARD)
			(dx = g->player.dir_x * PLAYER_SPEED, dy = g->player.dir_y * PLAYER_SPEED);
		else if (act == MOVE_BACKWARD)
			(dx = -g->player.dir_x * PLAYER_SPEED, dy = -g->player.dir_y * PLAYER_SPEED);
		else if (act == MOVE_RIGHT)
			(dx = -g->player.dir_y * PLAYER_SPEED, dy = g->player.dir_x * PLAYER_SPEED);
		else if (act == MOVE_LEFT)
			(dx = g->player.dir_y * PLAYER_SPEED, dy = -g->player.dir_x * PLAYER_SPEED);

		if (dx != 0.0 || dy != 0.0)
			apply_player_movement(g, dx, dy);
	}
}

void	player_controller(t_game *g)
{
	if (!g)
		return ;

	if (g->key.w)
		player_apply_action(g, MOVE_FORWARD);
	if (g->key.s)
		player_apply_action(g, MOVE_BACKWARD);
	if (g->key.d)
		player_apply_action(g, MOVE_RIGHT);
	if (g->key.a)
		player_apply_action(g, MOVE_LEFT);
	if (g->key.right)
		player_apply_action(g, ROTATE_RIGHT);
	if (g->key.left)
		player_apply_action(g, ROTATE_LEFT);
}
