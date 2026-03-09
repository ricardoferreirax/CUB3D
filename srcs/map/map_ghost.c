/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ghost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:37:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 23:05:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static void	free_copy_partial(char **map_copy, int rows_done)
{
	int	row;

	if (!map_copy)
		return ;
	row = 0;
	while (row < rows_done)
	{
		free(map_copy[row]);
		row++;
	}
	free(map_copy);
}

static void	copy_map_row(char *row_dst, const char *row_src)
{
	int	col;

	col = 0;
	while (row_src && row_src[col] != '\0')
	{
		if (row_src[col] == 'M')
			row_dst[col] = WALL;
		else if (row_src[col] == 'D')
			row_dst[col] = '0';
		else if (row_src[col] == '\n')
			row_dst[col] = '\0';
		else
			row_dst[col] = row_src[col];
		col++;
	}
	row_dst[col] = '\0';
}

char	**copy_map(char **map_grid)
{
	char	**map_copy;
	int		row;
	int		height;

	if (!map_grid)
		return (NULL);
	height = ytile(map_grid);
	map_copy = ft_calloc((size_t)height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	row = 0;
	while (row < height)
	{
		map_copy[row] = ft_calloc(ft_strlen(map_grid[row]) + 1, sizeof(char));
		if (!map_copy[row])
			return (free_copy_partial(map_copy, row), NULL);
		copy_map_row(map_copy[row], map_grid[row]);
		row++;
	}
	map_copy[row] = NULL;
	return (map_copy);
}

t_point	find_c(char **map_grid, char target)
{
	t_point	cord;

	cord.y = 0;
	while (map_grid && map_grid[cord.y])
	{
		cord.x = 0;
		while (map_grid[cord.y][cord.x])
		{
			if (map_grid[cord.y][cord.x] == target)
			{
				// cord.x *= 2;
				// cord.y *= 2;
				return (cord);
			}
			cord.x++;
		}
		cord.y++;
	}
	cord.x = -1;
	cord.y = -1;
	return (cord);
}
