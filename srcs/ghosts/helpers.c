/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:39:37 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/05 14:47:27 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

int	passed_center(t_ghost *ghost)
{
	int	center;
	int	passed_center;

	int cx, cy;
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

