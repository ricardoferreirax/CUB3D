/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:51:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/27 23:44:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

void	ghost_snap_center(t_ghost *gh)
{
	int	tx;
	int	ty;

	tx = (int)gh->pos.tile_pos.x;
	ty = (int)gh->pos.tile_pos.y;
	gh->pos.tile_pos.x = (double)tx + 0.5;
	gh->pos.tile_pos.y = (double)ty + 0.5;
}

int	ghost_at_center(t_ghost *gh)
{
	double	fx;
	double	fy;

	fx = gh->pos.tile_pos.x - (double)((int)gh->pos.tile_pos.x) - 0.5;
	if (fx < 0.0)
		fx = -fx;
	fy = gh->pos.tile_pos.y - (double)((int)gh->pos.tile_pos.y) - 0.5;
	if (fy < 0.0)
		fy = -fy;
	return (fx < 0.05 && fy < 0.05);
}

t_double_point	ghost_dir_delta(int dir)
{
	t_double_point	d;

	d.x = 0.0;
	d.y = 0.0;
	if (dir == 0)
		d.y = -1.0;
	else if (dir == 1)
		d.x = -1.0;
	else if (dir == 2)
		d.y = 1.0;
	else
		d.x = 1.0;
	return (d);
}

// dir: 0=up, 1=left, 2=down, 3=right 
t_point	ghost_next_tile(int gx, int gy, int dir)
{
	t_point	n;

	n.x = gx;
	n.y = gy;
	if (dir == 0)
		n.y = gy - 1;
	else if (dir == 1)
		n.x = gx - 1;
	else if (dir == 2)
		n.y = gy + 1;
	else
		n.x = gx + 1;
	return (n);
}

int	ghost_dist2_target(t_ghost *gh, t_point n)
{
	int	dx;
	int	dy;

	dx = n.x - gh->target_tile.x;
	dy = n.y - gh->target_tile.y;
	return (dx * dx + dy * dy);
}

int	ghost_opposite_dir(int dir)
{
	return ((dir + 2) % 4);
}

int	ghost_can_step(t_game *g, t_ghost *gh, int dir)
{
	t_point	n;

	n = ghost_next_tile((int)gh->pos.tile_pos.x, (int)gh->pos.tile_pos.y, dir);
	if (map_wrap_row_is_active(g, n.y))
	{
		if (n.x < 0)
			n.x = g->map.width - 1;
		else if (n.x >= g->map.width)
			n.x = 0;
	}
	return (!is_wall_ghost(g, n.y, n.x));
}

int	ghost_choose_next_dir(t_game *g, t_ghost *gh)
{
	t_point	n;
	int		dir;
	int		best_dir;
	int		best;

	dir = 0;
	best = -1;
	best_dir = -1;
	while (dir < 4)
	{
		if (dir != gh->invalid_dir)
		{
			n = ghost_next_tile((int)gh->pos.tile_pos.x,
					(int)gh->pos.tile_pos.y, dir);
			if (map_wrap_row_is_active(g, n.y))
			{
				if (n.x < 0)
					n.x = g->map.width - 1;
				else if (n.x >= g->map.width)
					n.x = 0;
			}
			if (!is_wall_ghost(g, n.y, n.x))
			{
				if (best == -1 || ghost_dist2_target(gh, n) < best)
				{
					best = ghost_dist2_target(gh, n);
					best_dir = dir;
				}
			}
		}
		dir++;
	}
	if (best_dir == -1)
		best_dir = ghost_opposite_dir(gh->invalid_dir);
	gh->invalid_dir = ghost_opposite_dir(best_dir);
	return (best_dir);
}

void	ghost_apply_move(t_game *g, t_ghost *gh, double dt)
{
	t_double_point	d;
	double		step;
	t_point		row;

	d = ghost_dir_delta(gh->cur_dir);
	step = gh->speed * dt;
	gh->pos.tile_pos.x += d.x * step;
	gh->pos.tile_pos.y += d.y * step;

	row.y = (int)gh->pos.tile_pos.y;
	row.x = 0;
	if (map_wrap_row_is_active(g, row.y))
	{
		if (gh->pos.tile_pos.x < 0.0)
			gh->pos.tile_pos.x += (double)g->map.width;
		else if (gh->pos.tile_pos.x >= (double)g->map.width)
			gh->pos.tile_pos.x -= (double)g->map.width;
	}
	gh->pos.pixel_pos.x = (gh->pos.tile_pos.x + 0.5) * (double)TILE_SIZE;
	gh->pos.pixel_pos.y = (gh->pos.tile_pos.y + 0.5) * (double)TILE_SIZE;
}

void	update_ghost(t_game *g, t_ghost *gh, double dt)
{
	int	dir;

	if (!g || !gh)
		return ;
	gh->target_tile.x = (int)g->player.pos_x;
	gh->target_tile.y = (int)g->player.pos_y;
	if (ghost_at_center(gh))
	{
		ghost_snap_center(gh);
		dir = ghost_choose_next_dir(g, gh);
		if (ghost_can_step(g, gh, dir))
			gh->cur_dir = dir;
	}
	if (!ghost_can_step(g, gh, gh->cur_dir))
	{
		dir = ghost_choose_next_dir(g, gh);
		if (!ghost_can_step(g, gh, dir))
			return ;
		gh->cur_dir = dir;
	}
	ghost_apply_move(g, gh, dt);
}

void	update_ghosts(t_game *g, double dt)
{
	int	i;

	if (!g)
		return ;
	i = 0;
	while (i < 4)
	{
		update_ghost(g, &g->ghosts[i], dt);
		i++;
	}
}
