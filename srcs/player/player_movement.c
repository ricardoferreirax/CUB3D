/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 05:09:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

/* static void	player_snap_axis(double *pos, double pull, double eps)
{
	double	center;
	double	d;

	center = (double)((int)(*pos)) + 0.5;
	d = center - *pos;
	if (d < 0.0)
		d = -d;
	if (d <= eps)
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

	if (!g)
		return ;
	ax = dx;
	if (ax < 0.0)
		ax = -ax;
	ay = dy;
	if (ay < 0.0)
		ay = -ay;
	if (ax > ay)
		player_snap_axis(&g->player.pos_y, PLAYER_SPEED * 0.50, 0.03);
	else
		player_snap_axis(&g->player.pos_x, PLAYER_SPEED * 0.50, 0.03);
} */

static void	player_move_left(t_game *g)
{
	double	dx;
	double	dy;

	dx =  g->player.dir_y * PLAYER_SPEED;
	dy = -g->player.dir_x * PLAYER_SPEED;
	//player_snap_for_move(g, dx, dy);
	move_radius_check(g, dx, dy);
}

static void	player_move_right(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_y * PLAYER_SPEED;
	dy =  g->player.dir_x * PLAYER_SPEED;
	//player_snap_for_move(g, dx, dy);
	move_radius_check(g, dx, dy);
}

static void	player_move_forward(t_game *g)
{
	double	dx;
	double	dy;

	dx = g->player.dir_x * PLAYER_SPEED;
	dy = g->player.dir_y * PLAYER_SPEED;
	//player_snap_for_move(g, dx, dy);
	move_radius_check(g, dx, dy);
}

static void	player_move_backward(t_game *g)
{
	double	dx;
	double	dy;

	dx = -g->player.dir_x * PLAYER_SPEED;
	dy = -g->player.dir_y * PLAYER_SPEED;
	//player_snap_for_move(g, dx, dy);
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
