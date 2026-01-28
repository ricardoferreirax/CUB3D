/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/28 17:05:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	flood_fill(t_game *g, int y, int x, char **vis)
{
	char	t;

	if (y < 0 || y >= g->map.height)
		exit_game(EXIT_MAP, g);
	if (x < 0)
	{
		if (map_tile(g, y, 0) != WRAP_PORTS || map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
			exit_game(EXIT_MAP, g);
		x = g->map.width - 1;
	}
	else if (x >= g->map.width)
	{
		if (map_tile(g, y, 0) != WRAP_PORTS || map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
			exit_game(EXIT_MAP, g);
		x = 0;
	}
	if (vis[y][x])
		return ;
	t = map_tile(g, y, x);
	if (t == VOID)
		exit_game(EXIT_MAP, g);
	if (t == WALL)
		return ;
	vis[y][x] = 1;
	flood_fill(g, y + 1, x, vis);
	flood_fill(g, y - 1, x, vis);
	flood_fill(g, y, x + 1, vis);
	flood_fill(g, y, x - 1, vis);
}

static char	**alloc_vis(int h, int w)
{
	char	**v;
	int		i;

	v = ft_calloc(h + 1, sizeof(char *));
	if (!v)
		return (NULL);
	i = 0;
	while (i < h)
	{
		v[i] = ft_calloc(w, sizeof(char));
		if (!v[i])
		{
			while (i > 0)
				free(v[--i]);
			free(v);
			return (NULL);
		}
		i++;
	}
	v[h] = NULL;
	return (v);
}

void	validate_map_flood_fill(t_game *g)
{
	char	**vis;
	int		px;
	int		py;

	vis = alloc_vis(g->map.height, g->map.width);
	if (!vis)
		exit_game(EXIT_MALLOC, g);

	px = (int)g->player.pos_x;
	py = (int)g->player.pos_y;

	flood_fill(g, py, px, vis);
	free_tab_tab(vis);
}


