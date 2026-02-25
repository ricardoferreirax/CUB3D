/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:35:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:04:36 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	map_line_len(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	map_setup_size(t_game *g)
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
		w = map_line_len(g->map.grid[y]);
		if (w > max_w)
			max_w = w;
		y++;
	}
	g->map.height = y;
	g->map.width = max_w;
}

static int	map_fill_row(t_game *g, char **rect, int y)
{
	int		x;
	int		len;
	char	c;

	rect[y] = ft_calloc(g->map.width + 1, sizeof(char));
	if (!rect[y])
		return (0);
	len = map_line_len(g->map.grid[y]);
	x = 0;
	while (x < g->map.width)
	{
		if (x < len)
		{
			c = g->map.grid[y][x];
			if (c == '\n' || c == VOID)
				rect[y][x] = WALL;
			else
				rect[y][x] = c;
		}
		else
			rect[y][x] = WALL;
		x++;
	}
	rect[y][g->map.width] = '\0';
	return (1);
}

char	**map_rectangular(t_game *g)
{
	char	**rect;
	int		y;

	rect = ft_calloc(g->map.height + 1, sizeof(char *));
	if (!rect)
		return (NULL);
	y = 0;
	while (y < g->map.height)
	{
		if (!map_fill_row(g, rect, y))
			return (free_tab_tab(rect), NULL);
		y++;
	}
	rect[y] = NULL;
	return (rect);
}
