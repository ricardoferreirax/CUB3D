/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:01:19 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/07 15:00:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	xtile(char **map)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (map && map[i])
	{
		if (total < (int)ft_strlen(map[i]))
			total = ft_strlen(map[i]);
		i++;
	}
	return (total);
}

int	ytile(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}


char	*parse_chars(char *str)
{
	char	*dup;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	dup = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\n')
		{
			if (str[i] == 'M')
				dup[j] = '1';
			else
				dup[j] = str[i];
			j++;
		}
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

char	**remove_char(char **array)
{
	int		i;
	char	**final;

	i = 0;
	final = ft_calloc(ytile(array) + 1, sizeof(char *));
	while (array[i] != NULL)
	{
		final[i] = parse_chars(array[i]);
		i++;
	}
	final[i] = NULL;
	return (final);
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

int	distance_squared(t_double_point a, t_double_point b)
{
	int	dx;
	int	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

bool	print_usage(void)
{
	ft_printf("Unkown arguments found\n");
	ft_printf("Usage: ./cub3d [FILE]... [OPTIONS]...\n");
	ft_printf("Runs Pac-Man 3D using X11\n");
	ft_printf("\n\n\tdebug_mode=y\tRuns the game in Debug Mode\n");
	ft_printf("\t[XX]\t\tSpecify a number for the controller event file.");
	ft_printf(" (see README.md for more details)\n");
	ft_printf("\n\n\tExamples:\n\t./cub3d map.cub 12 debug_mode=y\n");
	ft_printf("\t./cub3d ./path/to/file.cub\n");
	ft_printf("\t./cub3d map.cub debug_mode=y\n");
	return (true);
}
