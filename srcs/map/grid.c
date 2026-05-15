/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:40:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:50:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

int	map_row_last_col(t_game *g, int row, int want_wrap)
{
	int		last;
	char	*s;

	if (!g || !g->map.grid || row < 0 || row >= g->map.height)
		return (-1);
	s = g->map.grid[row];
	last = (int)ft_strlen(s) - 1;
	while (last >= 0 && s[last] == '\n')
		last--;
	if (!want_wrap)
		return (last);
	if (last < 1 || s[0] != WRAP_PORTS || s[last] != WRAP_PORTS)
		return (-1);
	return (last);
}

char	map_get_tile(t_game *game, int row, int col, int wrap)
{
	int	last_col;

	if (!game || !game->map.grid || row < 0 || row >= game->map.height)
		return (VOID);
	last_col = map_row_last_col(game, row, wrap);
	if (wrap && last_col >= 0)
	{
		if (col < 0)
			col = last_col;
		else if (col > last_col)
			col = 0;
	}
	else
		last_col = map_row_last_col(game, row, 0);
	if (col < 0 || col > last_col)
		return (VOID);
	if (game->map.grid[row][col] <= ' ')
		return (VOID);
	return (game->map.grid[row][col]);
}
