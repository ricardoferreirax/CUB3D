/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:58:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/29 22:10:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	is_wall_tile(char t)
{
	return (t == WALL);
}

int	is_void_tile(char t)
{
	return (t == VOID);
}

int	is_solid_tile(char t)
{
	return (t == WALL || t == VOID);
}

int	is_walkable_tile(char t)
{
	return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
		|| t == WRAP_PORTS || t == PLAYER
		|| t == 'N' || t == 'S' || t == 'E' || t == 'W');
}

static int	is_valid_wrap_port(t_game *g, int y, int x)
{
	if (map_tile(g, y, 0) != WRAP_PORTS)
		return (0);
	if (map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
		return (0);
	if (x != 0 && x != g->map.width - 1)
		return (0);
	if (map_tile(g, y - 1, x) == VOID || map_tile(g, y + 1, x) == VOID)
		return (0);
	if (x == 0 && !is_walkable_tile(map_tile(g, y, 1)))
		return (0);
	if (x == g->map.width - 1 && !is_walkable_tile(map_tile(g, y, g->map.width - 2)))
		return (0);
	return (1);
}

void	validate_map_closed(t_game *g)
{
	int		y;
	int		x;
	char	t;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			t = map_tile(g, y, x);
			if (is_walkable_tile(t))
			{
				if (t == WRAP_PORTS && is_valid_wrap_port(g, y, x))
				{
					x++;
					continue;
				}
				if (map_tile(g, y, x + 1) == VOID || map_tile(g, y, x - 1) == VOID
					|| map_tile(g, y + 1, x) == VOID || map_tile(g, y - 1, x) == VOID)
					exit_game(EXIT_MAP, g);
			}
			x++;
		}
		y++;
	}
}
