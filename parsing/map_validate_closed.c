/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:58:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/29 22:12:25 by rmedeiro         ###   ########.fr       */
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
