/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:33:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 12:02:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	free_lines_partial(char **lines, int n)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < n)
		free(lines[i++]);
	free(lines);
}

static int	count_lines_file(const char *path)
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

char	**map_read_file(const char *path)
{
	int		fd;
	int		n;
	int		i;
	char	**lines;
	char	*line;

	n = count_lines_file(path);
	if (n <= 0)
		return (NULL);
	lines = ft_calloc((size_t)n + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(lines), NULL);
	i = 0;
	while (i < n && (line = get_next_line(fd)))
	{
		lines[i] = ft_strdup(line);
		free(line);
		if (!lines[i])
		{
			close(fd);
			free_lines_partial(lines, i);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
