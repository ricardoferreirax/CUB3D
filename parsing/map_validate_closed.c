/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:58:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/28 17:13:53 by rmedeiro         ###   ########.fr       */
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

static int	is_border_allowed(char t)
{
	return (t == WALL || t == VOID || t == WRAP_PORTS);
}

static void	validate_border_rows(t_game *g)
{
	int	x;

	x = 0;
	while (x < g->map.width)
	{
		if (!is_border_allowed(map_tile(g, 0, x)))
			exit_game(EXIT_MAP, g);
		if (!is_border_allowed(map_tile(g, g->map.height - 1, x)))
			exit_game(EXIT_MAP, g);
		x++;
	}
}

static void	validate_border_cols(t_game *g)
{
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		if (!is_border_allowed(map_tile(g, y, 0)))
			exit_game(EXIT_MAP, g);
		if (!is_border_allowed(map_tile(g, y, g->map.width - 1)))
			exit_game(EXIT_MAP, g);
		y++;
	}
}

void	validate_map_closed(t_game *g)
{
	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	validate_border_rows(g);
	validate_border_cols(g);
}
