/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:53:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 21:14:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	map_is_valid_tile(char c)
{
	return 1;
	if (c == '\0')
		return (0);
	if (c == '\n')
		return (1);
	if (c == WALL || c == OPEN_SPACE || c == PACDOT || c == VOID)
		return (1);
	if (c == ENERGIZER || c == WRAP_PORTS)
		return (1);
	if (c == BLINKY_T || c == PINKY_T || c == INKY_T || c == CLYDE_T)
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == GATE)
		return (1);
	return (0);
}


void	map_validate_chars(t_game *g)
{
	int	y;
	int	x;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (!map_is_valid_tile(g->map.grid[y][x]))
				exit_game(EXIT_MAP, g);
			x++;
		}
		y++;
	}
}

void	map_validate_closed(t_game *g)
{
	int		y;
	int		x;
	char	t;
	int		check;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			t = map_get_tile(g, y, x);
			check = map_tile_type(t, TILE_WALKABLE)
				&& !(t == WRAP_PORTS && map_is_wrap_port(g, y, x));
			if (check && (map_tile_type(map_get_tile(g, y, x + 1), TILE_VOID)
					|| map_tile_type(map_get_tile(g, y, x - 1), TILE_VOID)
					|| map_tile_type(map_get_tile(g, y + 1, x), TILE_VOID)
					|| map_tile_type(map_get_tile(g, y - 1, x), TILE_VOID)))
				exit_game(EXIT_MAP, g);
			x++;
		}
		y++;
	}
}
