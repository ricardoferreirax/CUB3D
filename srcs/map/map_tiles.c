/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:15:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:19:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

char	map_tile(t_game *g, int y, int x)
{
	if (!g || !g->map.grid)
		return (VOID);
	if (y < 0 || x < 0 || y >= g->map.height || x >= g->map.width)
		return (VOID);
	return (g->map.grid[y][x]);
}

/* int	is_wall_tile(char t)
{
	return (t == WALL);
}

int	is_void_tile(char t)
{
	return (t == VOID);
}

int	is_solid_tile(char t)
{
	return (t == WALL);
}

int	is_walkable_tile(char t)
{
	return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
		|| t == WRAP_PORTS || t == 'N' || t == 'S' || t == 'E' || t == 'W');
} */

int	map_tile_type(char t, int tile_type)
{
	if (tile_type == TILE_WALL)
		return (t == WALL);
	if (tile_type == TILE_VOID)
		return (t == VOID);
	if (tile_type == TILE_SOLID)
		return (t == WALL);
	if (tile_type == TILE_WALKABLE)
	{
		return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
			|| t == WRAP_PORTS || t == 'N'
			|| t == 'S' || t == 'E' || t == 'W');
	}
	return (0);
}