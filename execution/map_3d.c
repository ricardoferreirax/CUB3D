/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:47:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/20 16:49:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static int	line_len_no_nl(const char *s)
{
	int	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	map_tile(t_game *g, int y, int x)
{
	if (!g || !g->map.grid)
		return (OPEN_SPACE);
	if (y < 0 || y >= g->map.height || !g->map.grid[y])
		return (OPEN_SPACE);
	if (x < 0 || x >= line_len_no_nl(g->map.grid[y]))
		return (OPEN_SPACE);
	return (g->map.grid[y][x]);
}

void	setup_map_grid(t_game *g)
{
	int	y;
	int	w;
	int	max_w;

	if (!g || !g->map.grid)
		return ;
	y = 0;
	max_w = 0;
	while (g->map.grid[y])
	{
		w = line_len_no_nl(g->map.grid[y]);
		if (w > max_w)
			max_w = w;
		y++;
	}
	g->map.height = y;
	g->map.width = max_w;
}
