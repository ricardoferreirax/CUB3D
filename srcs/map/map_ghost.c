/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ghost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:37:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/27 22:37:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static void	free_copy_partial(char **copy, int rows_done)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < rows_done)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

static void	copy_map_row(char *dst, const char *src)
{
	int	j;

	j = 0;
	while (src && src[j] != '\0')
	{
		if (src[j] == 'M')
			dst[j] = WALL;
		else
			dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
}

char	**copy_map(char **map)
{
	char	**copy;
	int		i;
	int		h;

	if (!map)
		return (NULL);
	h = ytile(map);
	copy = ft_calloc((size_t)h + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < h)
	{
		copy[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(char));
		if (!copy[i])
			return (free_copy_partial(copy, i), NULL);
		copy_map_row(copy[i], map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_point	find_c(char **map, char c)
{
	t_point	cord;

	cord.y = 0;
	while (map && map[cord.y])
	{
		cord.x = 0;
		while (map[cord.y][cord.x])
		{
			if (map[cord.y][cord.x] == c)
				return (cord);
			cord.x++;
		}
		cord.y++;
	}
	cord.x = -1;
	cord.y = -1;
	return (cord);
}
