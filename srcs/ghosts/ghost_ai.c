/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:22:16 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:19:42 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

int	is_ghost_on_deadend(t_game *game, t_ghost *ghost, int direction[4][2],
		int ignore_walls)
{
	t_point	next_tile;
	int		dir;

	dir = (ghost->invalid_dir + 2) % 4;
	next_tile.y = (ghost->pos.pixel_pos.y / TILE_SIZE) + direction[dir][0];
	next_tile.x = (ghost->pos.pixel_pos.x / TILE_SIZE) + direction[dir][1];
	if (!ignore_walls && in_bounds(&game->map, next_tile)
		&& (game->map.grid[next_tile.y][next_tile.x] == '1'
		|| game->map.grid[next_tile.y][next_tile.x] == 'G'))
	{
		if (passed_center(ghost))
		{
			ghost->invalid_dir = dir;
			dir = (dir + 2) % 4;
		}
	}
	return (dir);
}

void	ghost_move_pixel(t_ghost *gh, int dx, int dy)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x += dx;
	gh->pos.pixel_pos.y += dy;
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
}

bool	cannot_move_up(t_game *game, t_ghost *ghost)
{
	int	x;
	int	y;

	x = ghost->pos.pixel_pos.x / 8;
	y = ghost->pos.pixel_pos.y / 8;
	if (y == game->targets.player_spawn.y)
	{
		if (x > game->targets.player_spawn.x - 4
			&& x < game->targets.player_spawn.x + 4)
			return (true);
	}
	if (y == game->targets.ghost_house.y)
	{
		if (x > game->targets.ghost_house.x - 4
			&& x < game->targets.ghost_house.x + 4)
			return (true);
	}
	return (false);
}

void	ghost_set_pixel_pos(t_ghost *gh, double px, double py)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x = px;
	gh->pos.pixel_pos.y = py;
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
}

bool	ghost_ai(t_game *game, t_ghost *ghost)
{
	if (ghost->name == DISABLED)
		return (true);
	ghost_wrap_position(game, ghost);
	update_ghost(game, ghost);
	if (ghost->state != game->global_state && ghost->state != FRIGHTENED
		&& ghost->state != EATEN)
	{
		if (ghost->cruiser.is_blinky && (ghost->cruiser.one.enabled
				|| ghost->cruiser.two.enabled))
			ghost->state = CHASE;
		else
		{
			ghost->state = game->global_state;
			ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
		}
	}
	return (false);
}
