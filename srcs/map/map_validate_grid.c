/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:53:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 15:33:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	map_is_valid_tile(t_game *g, char c)
{
	return 1;
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
		if (c == PACDOT || c == ENERGIZER || c == WRAP_PORTS
			|| c == BLINKY_T || c == PINKY_T || c == INKY_T || c == CLYDE_T
			|| c == GATE || c == PLAYER)
			return (1);
	}
	return (0);
}

void	map_validate_chars(t_game *game)
{
	int		row;
	int		col;
	char	tile;

	if (!game || !game->map.grid)
		exit_game(EXIT_MAP, game, "map_validate_chars: missing grid");
	row = 0;
	while (game->map.grid[row])
	{
		col = 0;
		while (game->map.grid[row][col])
		{
			tile = game->map.grid[row][col];
			if (!map_is_valid_tile(game, tile))
				exit_game(EXIT_MAP, game, "map_validate_chars: invalid tile");
			col++;
		}
		row++;
	}
}

void	map_validate_closed(t_game *g)
{
	int		row;
	int		col;
	char	tile;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "map_validate_closed: missing grid");
	row = -1;
	while (++row < g->map.height)
	{
		col = -1;
		while (++col < g->map.width)
		{
			tile = map_get_tile(g, row, col);
			if (!map_tile_type(tile, TILE_WALKABLE)
				|| (tile == WRAP_PORTS && map_is_wrap_tile(g, row, col)))
				continue ;
			if (map_tile_type(map_get_tile(g, row, col + 1), TILE_VOID)
				|| map_tile_type(map_get_tile(g, row, col - 1), TILE_VOID)
				|| map_tile_type(map_get_tile(g, row + 1, col), TILE_VOID)
				|| map_tile_type(map_get_tile(g, row - 1, col), TILE_VOID))
				exit_game(EXIT_MAP, g, "map_validate_closed: map is not closed");
		}
	}
}
