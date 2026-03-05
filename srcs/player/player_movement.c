/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 17:36:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	player_move_left(t_game *g)
{
	double	dx;
	double	dy;

	dx =  g->player.dir_y * PLAYER_SPEED;
	dy = -g->player.dir_x * PLAYER_SPEED;
	apply_player_movement(g, dx, dy);
}

static void	player_move_right(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_y * PLAYER_SPEED;
	dy =  g->player.dir_x * PLAYER_SPEED;
	apply_player_movement(g, dx, dy);
}

static void	player_move_forward(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.dir_x * PLAYER_SPEED;
	dy = g->player.dir_y * PLAYER_SPEED;
	apply_player_movement(g, dx, dy);
}

static void	player_move_backward(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_x * PLAYER_SPEED;
	dy = -g->player.dir_y * PLAYER_SPEED;
	apply_player_movement(g, dx, dy);
}

void	player_movement_controller(t_game *g)
{
	if (g->key.w)
		player_move_forward(g);
	if (g->key.s)
		player_move_backward(g);
	if (g->key.d)
		player_move_right(g);
	if (g->key.a)
		player_move_left(g);
}
