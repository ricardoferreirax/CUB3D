/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:35:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:52:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	map_row_len(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	map_dimensions(t_game *g)
{
	int	row;
	int	row_len;
	int	max_row_len;

	if (!g || !g->map.grid)
		return ;
	row = 0;
	max_row_len = 0;
	while (g->map.grid[row])
	{
		row_len = map_row_len(g->map.grid[row]);
		if (row_len > max_row_len)
			max_row_len = row_len;
		row++;
	}
	g->map.height = row;
	g->map.width = max_row_len;
}

static int	map_fill_row(t_game *g, char **rect, int row)
{
	int		col;
	char	*map_row;
	char	c;

	rect[row] = ft_calloc((size_t)g->map.width + 1, sizeof(char));
	if (!rect[row])
		return (0);
	map_row = g->map.grid[row]; 
	col = 0;
	while (col < g->map.width) // enquanto houver colunas para preencher
	{
		c = '\0';
		if (map_row && *map_row && *map_row != '\n') // se ainda houver caracteres na row
			c = *map_row;
		if (c == '\t' || c == '\0')
			rect[row][col] = VOID;
		else // preencher com o caractere do mapa
			rect[row][col] = c;
		if (map_row && *map_row && *map_row != '\n')
			map_row++;
		col++;
	}
	rect[row][g->map.width] = '\0';
	return (1);
}

char	**map_rectangular(t_game *g)
{
	char	**rect;
	int		row;

	if (!g || !g->map.grid || g->map.width <= 0 || g->map.height <= 0)
		return (NULL);
	rect = ft_calloc((size_t)g->map.height + 1, sizeof(char *));
	if (!rect)
		return (NULL);
	row = 0;
	while (row < g->map.height)
	{
		if (!map_fill_row(g, rect, row))
			return (free_tab_tab(rect), NULL);
		row++;
	}
	rect[row] = NULL;
	return (rect);
}
