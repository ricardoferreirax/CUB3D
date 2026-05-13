/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:39:37 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:21:22 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

int	passed_center(t_ghost *ghost)
{
	int	center;
	int	passed_center;
	int	cx;
	int	cy;

	cx = ghost->pos.pixel_pos.x % TILE_SIZE;
	cy = ghost->pos.pixel_pos.y % TILE_SIZE;
	center = TILE_SIZE / 2;
	passed_center = 0;
	if (ghost->invalid_dir == 2)
		passed_center = (cy < center);
	if (ghost->invalid_dir == 3)
		passed_center = (cx < center);
	if (ghost->invalid_dir == 0)
		passed_center = (cy > center);
	if (ghost->invalid_dir == 1)
		passed_center = (cx > center);
	return (passed_center);
}

bool	in_bounds(t_map *map, t_point coord)
{
	if (coord.x < 0 || coord.y < 0)
		return (false);
	if (coord.x > map->width || coord.y > map->height)
		return (false);
	return (true);
}

int	rng_machine(void)
{
	int	rng_num;
	int	best_dir;

	best_dir = -1;
	rng_num = rand() % 8192;
	if (rng_num < 1338)
		best_dir = 0;
	else if (rng_num < 3402)
		best_dir = 3;
	else if (rng_num < 5740)
		best_dir = 2;
	else if (rng_num < 8192)
		best_dir = 1;
	return (best_dir);
}

bool	is_not_blocked(t_ghost *ghost, t_map *map, int direction[4][2], int i)
{
	t_point	point;

	point.y = ghost->pos.pixel_pos.y / TILE_SIZE + direction[i][0];
	point.x = ghost->pos.pixel_pos.x / TILE_SIZE + direction[i][1];
	if (!in_bounds(map, point))
		return (false);
	return (map->grid[point.y][point.x] != '1'
		&& map->grid[point.y][point.x] != 'G' && i != ghost->invalid_dir);
}
