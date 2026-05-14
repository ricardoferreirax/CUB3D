/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:53:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:11:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	map_is_valid_tile(t_game *g, char c)
{
	if (c == '\0')
		return (0);
	if (c == '\n')
		return (1);
	if (c == WALL || c == OPEN_SPACE || c == VOID || c == 'M')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (g->mode == MODE_PACMAN)
	{
		if (c == PACDOT || c == ENERGIZER || c == WRAP_PORTS || c == BLINKY_T
			|| c == PINKY_T || c == INKY_T || c == CLYDE_T || c == GATE
			|| c == PLAYER)
			return (1);
	}
	return (0);
}

void	map_validate_tiles(t_game *g)
{
	int		y;
	int		x;
	char	tile;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "map_validate_tiles: missing grid");
	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			tile = g->map.grid[y][x];
			if (!map_is_valid_tile(g, tile))
				exit_game(EXIT_MAP, g, "map_validate_tiles: invalid tile");
			x++;
		}
		y++;
	}
}

void	map_validate_bounds(t_game *g)
{
	int		y;
	int		x;
	char	tile;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "map_validate_closed: missing grid");
	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			tile = map_get_tile_raw(g, y, x);
			if (!map_tile_type(tile, TILE_WALKABLE))
				continue ;
			if (tile == WRAP_PORTS && map_is_wrap_tile(g, y, x))
				continue ;
			if (map_tile_type(map_get_tile_raw(g, y, x + 1), TILE_VOID)
				|| map_tile_type(map_get_tile_raw(g, y, x - 1), TILE_VOID)
				|| map_tile_type(map_get_tile_raw(g, y + 1, x), TILE_VOID)
				|| map_tile_type(map_get_tile_raw(g, y - 1, x), TILE_VOID))
				exit_game(EXIT_MAP, g, "map_validate_closed: map not closed");
		}
	}
}
