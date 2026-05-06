/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:56:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 17:20:54 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../../srcs/render/render3D.h"
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

void	play_death(t_game *game, t_point coord)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.death[i]);
		mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
			game->win.frame_buffer.img_ptr, 0, 0);
		usleep(pow(10, 5));
		i++;
	}
	ft_printf("YOU ARE DEAD\n");
}

static void	apply_player_movement(t_game *g, double dx, double dy)
{
	int	slayer;

	if (g->mode == MODE_PACMAN)
		player_snap_for_move(g, dx, dy);
	player_collision(g);
	player_wrap_position(g);
	if (!player_collect_pacdots(g) && !player_collect_energizer(g))
	{
		g->player.pos.tile_pos.x += dx;
		g->player.pos.tile_pos.y += dy;
	}
	if ((slayer = player_touched_ghost(g)))
	{
		if (g->ghosts[slayer - 1].state == FRIGHTENED)
			g->ghosts[slayer - 1].state = EATEN;
		else
		{
			if (!g->debug_mode)
			{
				g->player.lives--;
				if (g->player.lives <= 0)
					exit_game(EXIT_FAILURE, g, "You are dead");
				play_death(g, (t_point){.x = g->player.pos.pixel_pos.x,
					.y = g->player.pos.pixel_pos.y});
				reset_game(g, 1);
			}
		}
	}
	if (g->player.collected_dots >= g->pacdot_count + g->energizer_count
		&& g->player.collected_dots != 0)
		reset_game(g, 0);
}

void	player_rotate(t_game *g, double angle)
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

static bool	safe_is_wall(t_map map, int y, int x)
{
	if (y < 0 || y >= map.height)
		return (true); // treat out of bounds as blocked
	if (x < 0)
		return (true);
	if (x >= (int)ft_strlen(map.grid[y]))
		return (true);
	return (map.grid[y][x] == '1');
}

bool	can_move(t_game *game, int dir)
{
	int	y;
	int	x;

	static int direction[4][2] = {
		{-1, 0}, // up
		{0, -1}, // left
		{1, 0},  // down
		{0, 1}   // right
	};
	y = (int)game->player.pos.tile_pos.y + direction[dir][0];
	x = (int)game->player.pos.tile_pos.x + direction[dir][1];
	if (safe_is_wall(game->map, y, x))
		return (false);
	return (true);
}

void	player_move(t_game *game, int dir)
{
	if (dir == 0 && can_move(game, dir))
	{
		game->player.target_dir.x = 0;
		game->player.target_dir.y = -1;
		game->player.target_plane.x = 0.66;
		game->player.target_plane.y = 0;
	}
	if (dir == 1 && can_move(game, dir))
	{
		game->player.target_dir.x = -1;
		game->player.target_dir.y = 0;
		game->player.target_plane.x = 0;
		game->player.target_plane.y = -0.66;
	}
	if (dir == 2 && can_move(game, dir))
	{
		game->player.target_dir.x = 0;
		game->player.target_dir.y = 1;
		game->player.target_plane.x = -0.66;
		game->player.target_plane.y = 0;
	}
	if (dir == 3 && can_move(game, dir))
	{
		game->player.target_dir.x = 1;
		game->player.target_dir.y = 0;
		game->player.target_plane.x = 0;
		game->player.target_plane.y = 0.66;
	}
}

void	update_player_direction(t_game *game, double dt)
{
	double	speed;

	speed = 0.5 * dt;
	(void)dt;
	game->player.dir.x += (game->player.target_dir.x - game->player.dir.x)
		* speed;
	game->player.dir.y += (game->player.target_dir.y - game->player.dir.y)
		* speed;
	game->player.plane.x += (game->player.target_plane.x - game->player.plane.x)
		* speed;
	game->player.plane.y += (game->player.target_plane.y - game->player.plane.y)
		* speed;
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
	else if (g->mode == MODE_PACMAN)
	{
		if (g->key.w || g->key.up)
			player_move(g, 0);
		if (g->key.s || g->key.down)
			player_move(g, 2);
		if (g->key.d || g->key.right)
			player_move(g, 3);
		if (g->key.a || g->key.left)
			player_move(g, 1);
		update_player_direction(g, 1);
		apply_player_movement(g, (g->player.target_dir.x * (PLAYER_SPEED + 0
					* (double)g->player.speed_multiplier / 100)),
			g->player.target_dir.y * (PLAYER_SPEED + 0
				* (double)g->player.speed_multiplier / 100));
	}
}
