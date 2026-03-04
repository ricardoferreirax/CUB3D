/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:41:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/04 10:24:45 by rmedeiro         ###   ########.fr       */
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

// retorna a ultima coluna de uma linha ou a ultima coluna wrap se existirem wrap tunnels
int	map_row_last_col(t_game *g, int row, int want_wrap)
{
	int		last;
	char	*s;

	if (!g || !g->map.grid || row < 0 || row >= g->map.height)
		return (-1);
	s = g->map.grid[row];
	last = (int)ft_strlen(s) - 1;
	while (last >= 0 && (s[last] == '\n' || s[last] == '\r'))
		last--;
	if (!want_wrap)
		return (last);
	if (last < 1)
		return (-1);
	if (s[0] != WRAP_PORTS || s[last] != WRAP_PORTS)
		return (-1);
	return (last);
}

char	map_get_tile(t_game *g, int y, int x)
{
	int		last;
	char	tile;

	if (!g || !g->map.grid || y < 0 || y >= g->map.height)
		return (VOID);
	last = map_row_last_col(g, y, 1);
	if (last >= 0)
	{
		if (x < 0)
			x = last;
		else if (x > last)
			x = 0;
	}
	else
		last = map_row_last_col(g, y, 0);
	if (x < 0 || x > last)
		return (VOID);
	tile = g->map.grid[y][x];
	if (tile == ' ' || tile == '\t' || tile == '\n' || tile == '\r' || tile == '\0')
		return (VOID);
	return (tile);
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
