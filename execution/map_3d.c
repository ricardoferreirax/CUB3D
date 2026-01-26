/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:47:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/26 22:42:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	in_bounds(t_game *g, int y, int x)
{
	if (!g)
		return (0);
	if (y < 0 || y >= g->map.height)
		return (0);
	if (x < 0 || x >= g->map.width)
		return (0);
	return (1);
}

char	map_tile(t_game *g, int y, int x)
{
	int	row_len;

	if (!in_bounds(g, y, x))
		return (WALL);
	if (!g->map.grid || !g->map.grid[y])
		return (WALL);
	row_len = line_len_no_nl(g->map.grid[y]);
	if (x >= row_len)
		return (WALL);
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
