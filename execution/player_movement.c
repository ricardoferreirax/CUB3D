/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 21:21:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	player_move_left(t_game *g)
{
	double	dx;
	double	dy;

	dx =  g->player.dir_y * PLAYER_SPEED;
	dy = -g->player.dir_x * PLAYER_SPEED;
	move_radius_check(g, dx, dy);
}

static void	player_move_right(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_y * PLAYER_SPEED;
	dy =  g->player.dir_x * PLAYER_SPEED;
	move_radius_check(g, dx, dy);
}

static void	player_move_forward(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.dir_x * PLAYER_SPEED;
	dy = g->player.dir_y * PLAYER_SPEED;
	move_radius_check(g, dx, dy);
}

static void	player_move_backward(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_x * PLAYER_SPEED;
	dy = -g->player.dir_y * PLAYER_SPEED;
	move_radius_check(g, dx, dy);
}

void	movement_controller(t_game *g)
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
