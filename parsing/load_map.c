/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:40:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 17:31:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	find_map_start(char **file)
{
	int	i;

	i = 0;
	while (file && file[i])
	{
		if (is_map_line(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	find_map_end(char **file, int start)
{
	int	i;
	int	last;

	i = start;
	last = -1;
	while (file && file[i])
	{
		if (is_map_line(file[i]))
			last = i;
		else if (!is_empty_line(file[i]))
			break; // encontrou algo nao vazio que não e o mapa
		i++;
	}
	return (last);
}

static char	**extract_map(char **file, int start, int end, t_game *g)
{
	int		i;
	int		j;
	int		n;
	char	**map;

	n = end - start + 1;
	if (n <= 0)
		return (NULL);
	map = ft_calloc((size_t)n + 1, sizeof(char *));
	if (!map)
		exit_game(EXIT_MALLOC, g);
	i = start;
	j = 0;
	while (i <= end)
	{
		map[j] = ft_strdup(file[i]);
		if (!map[j])
		{
			free_tab_tab(map);
			exit_game(EXIT_MALLOC, g);
		}
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}

char	**load_map_from_cub(t_game *g, const char *path)
{
	char	**file;
	int		start;
	int		end;
	char	**map;

	file = map_read_file(path);
	if (!file)
		exit_game(EXIT_MAP, g);
	start = find_map_start(file);
	if (start < 0)
	{
		free_tab_tab(file);
		exit_game(EXIT_MAP, g);
	}
	end = find_map_end(file, start);
	if (end < 0)
	{
		free_tab_tab(file);
		exit_game(EXIT_MAP, g);
	}
	// check_no_trailing_garbage(file, end);
	map = extract_map(file, start, end, g);
	free_tab_tab(file);
	if (!map)
		exit_game(EXIT_MAP, g);
	return (map);
}
