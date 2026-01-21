/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:47:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/20 17:42:52 by rmedeiro         ###   ########.fr       */
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

static int	in_bounds(t_game *g, int y, int x)
{
	return (y >= 0 && y < g->map.height && x >= 0 && x < g->map.width);
}

char	map_tile(t_game *g, int y, int x)
{
	if (!in_bounds(g, y, x))
		return (WALL); // trata fora do mapa como parede
	if (!g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y])
		|| g->map.grid[y][x] == '\n' || g->map.grid[y][x] == '\0')
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
