/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:33:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 17:34:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

void	player_rotate(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos_a - g->player.dir.y * sin_a;
	g->player.dir.y = old_dir_x * sin_a + g->player.dir.y * cos_a;
	old_plane_x = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos_a - g->player.plane.y * sin_a;
	g->player.plane.y = old_plane_x * sin_a + g->player.plane.y * cos_a;
}

void	player_apply_action(t_game *g, t_player_action act)
{
	if (act == MOVE_FORWARD)
		apply_player_movement(g, g->player.dir.x * PLAYER_SPEED,
			g->player.dir.y * PLAYER_SPEED);
	else if (act == MOVE_BACKWARD)
		apply_player_movement(g, -g->player.dir.x * PLAYER_SPEED,
			-g->player.dir.y * PLAYER_SPEED);
	else if (act == MOVE_RIGHT)
		apply_player_movement(g, -g->player.dir.y * PLAYER_SPEED,
			g->player.dir.x * PLAYER_SPEED);
	else if (act == MOVE_LEFT)
		apply_player_movement(g, g->player.dir.y * PLAYER_SPEED,
			-g->player.dir.x * PLAYER_SPEED);
	else if (act == ROTATE_RIGHT)
		player_rotate(g, ROT_SPEED);
	else if (act == ROTATE_LEFT)
		player_rotate(g, -ROT_SPEED);
}
