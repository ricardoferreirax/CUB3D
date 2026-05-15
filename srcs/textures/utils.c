/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:17:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 18:11:28 by rmedeiro         ###   ########.fr       */
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

int	set_texture_path(char **dest, char *value)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		return (0);
	if (*dest)
		return (0);
	*dest = ft_strdup(value);
	if (!*dest)
		return (-1);
	return (1);
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
