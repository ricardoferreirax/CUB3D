/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:33:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:10:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "map3D.h"

static void	map_free_lines(char **lines, int n)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < n)
		free(lines[i++]);
	free(lines);
}

static int	map_count_file_lines(const char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int	map_read_lines(int fd, char **lines, int n)
{
	int		i;
	char	*line;

	i = 0;
	while (i < n && (line = get_next_line(fd)))
	{
		lines[i] = ft_strdup(line);
		free(line);
		if (!lines[i])
			return (map_free_lines(lines, i), 0);
		i++;
	}
	lines[i] = NULL;
	return (1);
}

char	**map_read_file(const char *path)
{
	int		fd;
	int		n;
	char	**lines;

	n = map_count_file_lines(path);
	if (n <= 0)
		return (NULL);
	lines = ft_calloc((size_t)n + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(lines), NULL);
	if (!map_read_lines(fd, lines, n))
		return (close(fd), map_free_lines(lines, n), NULL);
	close(fd);
	return (lines);
}
