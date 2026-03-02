/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:40:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 22:16:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	find_map_start(t_game *g, char **file)
{
	int	i;

	i = 0;
	while (file && file[i])
	{
		if (map_is_map_line(g, file[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	find_map_end(t_game *g, char **file, int start)
{
	int	i;
	int	last;

	i = start;
	last = -1;
	while (file && file[i])
	{
		if (map_is_map_line(g, file[i]))
			last = i;
		else if (!map_is_empty_line(file[i]))
			break;
		i++;
	}
	return (last);
}

static char	**extract_map(char **file_lines, int start, int end, t_game *g)
{
	int		i;
	int		j;
	int		line_count;
	char	**map;

	if (!file_lines || start < 0 || end < start)
		return (NULL);
	line_count = end - start + 1;
	map = ft_calloc((size_t)line_count + 1, sizeof(char *));
	if (!map)
		exit_game(EXIT_MALLOC, g);
	i = start - 1;
	j = -1;
	while (++i <= end)
	{
		map[++j] = ft_strdup(file_lines[i]);
		if (!map[j])
		{
			map[j] = NULL;
			free_2d((void *)map);
			exit_game(EXIT_MALLOC, g);
		}
	}
	map[j + 1] = NULL;
	return (map);
}

char	**load_map_from_cub(t_game *g, const char *path)
{
	char	**file_lines;
	int		start;
	int		end;
	char	**map;

	file_lines = map_read_file(path);
	if (!file_lines)
		exit_game(EXIT_MAP, g);
	start = find_map_start(g, file_lines);
	if (start < 0)
	{
		free_2d((void *)file_lines);
		exit_game(EXIT_MAP, g);
	}
	end = find_map_end(g, file_lines, start);
	if (end < 0)
	{
		free_2d((void *)file_lines);
		exit_game(EXIT_MAP, g);
	}
	map = extract_map(file_lines, start, end, g);
	free_2d((void *)file_lines);
	if (!map)
		exit_game(EXIT_MAP, g);
	return (map);
}
