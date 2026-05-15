/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_next_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:40:14 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:20:06 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"
#include "../utils/helpers.h"

static int	chose_frightened_dir(t_ghost *ghost, t_map *map,
		int direction[4][2])
{
	int		best_dir;
	int		tries;
	t_point	check_dir;

	best_dir = rng_machine();
	tries = 0;
	while (tries < 4)
	{
		check_dir.x = ghost->pos.pixel_pos.x / TILE_SIZE
			+ direction[best_dir][1];
		check_dir.y = ghost->pos.pixel_pos.y / TILE_SIZE
			+ direction[best_dir][0];
		if (in_bounds(map, check_dir)
			&& ((map->grid[check_dir.y][check_dir.x] != '1'
				&& map->grid[check_dir.y][check_dir.x] != 'G')
				&& best_dir != ghost->invalid_dir))
			break ;
		best_dir = (best_dir + 3) % 4;
		tries++;
	}
	return (best_dir);
}

static int	chose_next_dir(t_ghost *ghost, t_map *map, int direction[4][2])
{
	int		i;
	t_point	target;
	int		dist;
	int		best;
	int		best_dir;

	i = -1;
	best = -1;
	best_dir = -1;
	target = ghost->target_tile;
	while (++i < 4)
	{
		if (is_not_blocked(ghost, map, direction, i))
		{
			dist = squared_distance(ghost->pos.pixel_pos.x / TILE_SIZE
					+ direction[i][1], ghost->pos.pixel_pos.y / TILE_SIZE
					+ direction[i][0], target.x, target.y);
			if (best == -1 || dist < best)
			{
				best = dist;
				best_dir = i;
			}
		}
	}
	return (best_dir);
}

int				g_direction[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int	chose_next_move(t_game *game, t_ghost *ghost, t_map *map)
{
	int	best_dir;

	best_dir = -1;
	if (!map)
		return (-1);
	if (ghost->state == FRIGHTENED)
		best_dir = chose_frightened_dir(ghost, map, g_direction);
	else
		best_dir = chose_next_dir(ghost, map, g_direction);
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	if (best_dir == 0 && cannot_move_up(game, ghost))
		return (ghost_move_pixel(ghost, g_direction[(ghost->invalid_dir + 2)
					% 4][1], g_direction[(ghost->invalid_dir + 2) % 4][0]),
			ghost->invalid_dir);
	ghost_move_pixel(ghost, g_direction[best_dir][1], g_direction[best_dir][0]);
	return ((best_dir + 2) % 4);
}

t_double_point	continue_travel(t_game *game, t_ghost *ghost, int ignore_walls)
{
	int	dir;
	int	runnning;

	dir = (ghost->invalid_dir + 2) % 4;
	runnning = 0;
	if (ghost->state == EATEN)
		runnning = 100;
	if (ghost->state == FRIGHTENED)
		ghost->speed_accumulador += ghost->speed_frightened;
	else
		ghost->speed_accumulador += ghost->speed_multiplier + runnning;
	if (ghost->speed_accumulador >= 100)
	{
		ghost->speed_accumulador -= 100;
		dir = is_ghost_on_deadend(game, ghost, g_direction, ignore_walls);
		return ((t_double_point){.x = ghost->pos.pixel_pos.x
			+ g_direction[dir][1], .y = ghost->pos.pixel_pos.y
			+ g_direction[dir][0]});
	}
	return ((t_double_point){.x = ghost->pos.pixel_pos.x,
		.y = ghost->pos.pixel_pos.y});
}
