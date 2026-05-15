/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:57:15 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/14 22:52:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../base/base.h"
#include "../player/player3D.h"
#include "map3D.h"

static int	is_walkable_open(t_game *g, int y, int x)
{
	if (map_tile_type(map_get_tile(g, y, x + 1, 0), TILE_VOID))
		return (1);
	if (map_tile_type(map_get_tile(g, y, x - 1, 0), TILE_VOID))
		return (1);
	if (map_tile_type(map_get_tile(g, y + 1, x, 0), TILE_VOID))
		return (1);
	if (map_tile_type(map_get_tile(g, y - 1, x, 0), TILE_VOID))
		return (1);
	return (0);
}

static void	check_walkable_bounds(t_game *g)
{
	int		y;
	int		x;
	char	tile;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			tile = map_get_tile(g, y, x, 0);
			if (!map_tile_type(tile, TILE_WALKABLE))
				continue ;
			if (tile == WRAP_PORTS && map_is_wrap_tile(g, y, x))
				continue ;
			if (is_walkable_open(g, y, x))
				exit_game(EXIT_MAP, g, "map_validate_bounds: map not closed");
		}
	}
}

static void	check_flood_void(t_game *g, char **tmp)
{
	int	y;
	int	x;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			if (g->map.grid[y][x] == ' ' && tmp[y][x] == 'F')
			{
				free_2d((void **)tmp);
				exit_game(EXIT_MAP, g, "map_validate_bounds: void reachable");
			}
		}
	}
}

static void	check_flood_bounds(t_game *g)
{
	char	**tmp;
	t_point	spawn;

	spawn = find_player_spawn(g);
	tmp = copy_map(g->map.grid);
	if (!tmp)
		exit_game(EXIT_MALLOC, g, "map_validate_bounds: malloc failed");
	flood_fill(tmp, spawn.x, spawn.y);
	check_flood_void(g, tmp);
	free_2d((void **)tmp);
}

void	map_validate_bounds(t_game *g)
{
	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "map_validate_bounds: missing grid");
	check_walkable_bounds(g);
	check_flood_bounds(g);
}
