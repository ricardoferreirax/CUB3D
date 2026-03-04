/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:41:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/04 09:50:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	map_tile_type(char t, int tile_type)
{
	if (tile_type == TILE_WALL)
		return (t == WALL || t == 'M');
	if (tile_type == TILE_VOID)
		return (t == VOID);
	if (tile_type == TILE_SOLID)
		return (t == WALL || t == 'M' || t == GATE);
	if (tile_type == TILE_WALKABLE)
	{
		return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
			|| t == WRAP_PORTS
			|| t == 'N' || t == 'S' || t == 'E' || t == 'W');
	}
	return (0);
}

char	map_get_tile(t_game *g, int y, int x)
{
	int		last;
	char	t;

	if (!g || !g->map.grid)
		return (VOID);
	if (y < 0 || y >= g->map.height)
		return (VOID);
	last = map_wrap_last_col(g, y);
	if (last >= 0)
	{
		if (x < 0)
			x = last;
		else if (x > last)
			x = 0;
	}
	else
	{
		last = (int)ft_strlen(g->map.grid[y]) - 1;
		while (last >= 0
			&& (g->map.grid[y][last] == '\n' || g->map.grid[y][last] == '\r'))
			last--;
	}
	if (x < 0 || x > last)
		return (VOID);
	t = g->map.grid[y][x];
	if (t == ' ' || t == '\t')
		return (VOID);
	return (t);
}

int	map_is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
