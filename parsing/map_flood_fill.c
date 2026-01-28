/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/28 17:11:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	flood_fill(t_game *g, int y, int x, char **visited)
{
	char	tile;

	if (y < 0 || y >= g->map.height)
		exit_game(EXIT_MAP, g);
	if (x < 0)
	{
		if (map_tile(g, y, 0) != WRAP_PORTS
			|| map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
			exit_game(EXIT_MAP, g);
		x = g->map.width - 1;
	}
	else if (x >= g->map.width)
	{
		if (map_tile(g, y, 0) != WRAP_PORTS
			|| map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
			exit_game(EXIT_MAP, g);
		x = 0;
	}
	if (visited[y][x])
		return ;
	tile = map_tile(g, y, x);
	if (tile == VOID)
		exit_game(EXIT_MAP, g);
	if (tile == WALL)
		return ;
	visited[y][x] = 1;
	flood_fill(g, y + 1, x, visited);
	flood_fill(g, y - 1, x, visited);
	flood_fill(g, y, x + 1, visited);
	flood_fill(g, y, x - 1, visited);
}

static char	**alloc_visited_grid(int h, int w)
{
	char	**grid;
	int		i;

	grid = ft_calloc(h + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < h)
	{
		grid[i] = ft_calloc(w, sizeof(char));
		if (!grid[i])
		{
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	grid[h] = NULL;
	return (grid);
}

void	validate_map_flood_fill(t_game *g)
{
	char	**visited;
	int		px;
	int		py;

	visited = alloc_visited_grid(g->map.height, g->map.width);
	if (!visited)
		exit_game(EXIT_MALLOC, g);
	px = (int)g->player.pos_x;
	py = (int)g->player.pos_y;
	flood_fill(g, py, px, visited);
	free_tab_tab(visited);
}
