/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:00:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/16 20:00:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

static void	strip_trailing_spaces(char *s)
{
	int	i;

	if (!s)
		return ;
	i = ft_strlen(s) - 1;
	while (i >= 0 && (s[i] == ' '))
	{
		s[i] = '\0';
		i--;
	}
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
	strip_trailing_spaces(value);
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
