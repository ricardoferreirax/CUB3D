/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 21:55:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	player_snap_axis(double *pos, double pull, double eps)
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
		player_snap_axis(&g->player.pos.tile_pos.y, PLAYER_SPEED * 0.50, 0.03);
	else
		player_snap_axis(&g->player.pos.tile_pos.x, PLAYER_SPEED * 0.50, 0.03);
}

static void	apply_player_movement(t_game *g, double dx, double dy)
{
	if(g->mode == MODE_PACMAN)
		player_snap_for_move(g, dx, dy);
	player_collision(g);
	player_wrap_position(g);
	if(!player_collect_pacdots(g))
	{
		g->player.pos.tile_pos.x += dx;
		g->player.pos.tile_pos.y += dy;
	}
}

static void	player_rotate(t_game *g, double angle)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	prev_dir_x = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos_a - g->player.dir.y * sin_a;
	g->player.dir.y = prev_dir_x * sin_a + g->player.dir.y * cos_a;
	prev_plane_x = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos_a - g->player.plane.y * sin_a;
	g->player.plane.y = prev_plane_x * sin_a + g->player.plane.y * cos_a;
}

static void	player_apply_action(t_game *g, t_player_action act)
{
	if (act == MOVE_FORWARD)
		apply_player_movement(g, g->player.dir.x * PLAYER_SPEED, g->player.dir.y
			* PLAYER_SPEED);
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

bool can_move(t_game *game, int dir)
{

	int direction[4][2] = {
		{-1, 0}, // 0 = up
		{0, -1}, // 1 = left
		{1, 0},  // 2 = down
		{0, 1}   // 3 = right
	};
	if(game->map.grid[(int)game->player.pos.tile_pos.y + direction[dir][0]][(int)game->player.pos.tile_pos.x + direction[dir][1]] == '1')
		return false;
	return true;
}

void move(t_game *game, int dir)
{
	if(dir == 0 && can_move(game, dir))
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	if(dir == 1 && can_move(game, dir))
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	if(dir == 2 && can_move(game, dir))
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	if(dir == 3 && can_move(game, dir))
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
}


void	player_controller(t_game *g)
{
	if (!g)
		return ;
	if (g->mode == MODE_CUBE)
	{
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
	else if(g->mode == MODE_PACMAN)
	{
		if (g->key.w)
			move(g, 0);
		if (g->key.s)
			move(g, 2);
		if (g->key.d)
			move(g, 3);
		if (g->key.a)
			move(g, 1);
		apply_player_movement(g, g->player.dir.x * PLAYER_SPEED, g->player.dir.y * PLAYER_SPEED);
	}
}
