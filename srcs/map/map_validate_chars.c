/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:53:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:25:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	is_valid_map_char(char c)
{
	if (c == '\n')
		return (1);
	if (c == WALL || c == OPEN_SPACE || c == PACDOT || c == VOID)
		return (1);
	if (c == ENERGIZER || c == WRAP_PORTS || c == GHOST_SPAWN)
		return (1);
	if (c == BLINKY_T || c == PINKY_T || c == INKY_T || c == CLYDE_T)
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	validate_map_chars(t_game *g)
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
			if (!is_valid_map_char(g->map.grid[y][x]))
				exit_game(EXIT_MAP, g);
			x++;
		}
		y++;
	}
}

void	validate_map_closed(t_game *g)
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
			t = map_tile(g, y, x);
			check = map_tile_type(t, TILE_WALKABLE) 
				&& !(t == WRAP_PORTS && is_valid_wrap_port(g, y, x));
			if (check && (map_tile_type(map_tile(g, y, x + 1), TILE_VOID)
				|| map_tile_type(map_tile(g, y, x - 1), TILE_VOID)
				|| map_tile_type(map_tile(g, y + 1, x), TILE_VOID)
				|| map_tile_type(map_tile(g, y - 1, x), TILE_VOID)))
				exit_game(EXIT_MAP, g);
			x++;
		}
		y++;
	}
}
