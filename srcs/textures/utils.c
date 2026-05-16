/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:17:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/16 19:39:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

void	strip_newline(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	s[i] = '\0';
}

char	*skip_whitespace(char *s)
{
	while (s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

int	is_map_start_line(t_game *g, char *line)
{
	return (map_is_map_line(g, line));
}

static int	texture_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	set_texture_path(char **dest, char *value)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (*dest)
		return (TEX_REPEATED);
	if (!*value)
		return (TEX_BAD_PATH);
	if (!is_xpm_path(value))
		return (TEX_BAD_PATH);
	if (!texture_file_exists(value))
		return (TEX_BAD_PATH);
	*dest = ft_strdup(value);
	if (!*dest)
		return (TEX_INVALID);
	return (TEX_OK);
}
