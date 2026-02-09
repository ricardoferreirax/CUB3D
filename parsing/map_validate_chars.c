/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:53:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/29 21:40:20 by rmedeiro         ###   ########.fr       */
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
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == PLAYER)
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
