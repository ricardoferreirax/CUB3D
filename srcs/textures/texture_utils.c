/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:17:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 21:28:16 by rmedeiro         ###   ########.fr       */
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

void	set_texture_path(char **dest, char *value, t_game *g)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		exit_game(EXIT_MAP, g, "set_texture_path() has found an invalid value");
	if (*dest)
		exit_game(EXIT_MAP, g, "set_texture_path() has found an invalid dst");
	*dest = ft_strdup(value);
	if (!*dest)
		exit_game(EXIT_MALLOC, g, "set_texture_path was unable to create a valid dst");
}

int	is_xpm_path(const char *s)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	len = 0;
	while (s[i + len] && s[i + len] != '\n' && s[i + len] != '\r'
		&& s[i + len] != ' ' && s[i + len] != '\t')
		len++;
	if (len < 4)
		return (0);
	return (s[i + len - 4] == '.' && s[i + len - 3] == 'x'
		&& s[i + len - 2] == 'p' && s[i + len - 1] == 'm');
}
