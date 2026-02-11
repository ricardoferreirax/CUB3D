/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 17:21:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_empty_line(char *s)
{
	int i = 0;

	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != '\n' && !is_whitespace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_cub_prefix(char *p)
{
	return (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
		|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2)
		|| *p == 'F' || *p == 'C');
}

int	is_valid_map_char(char c)
{
	return (c == '\n' || c == ' ' || c == '\t' || c == WALL || c == OPEN_SPACE 
		|| c == PACDOT || c == WRAP_PORTS || c == GHOST_SPAWN || c == BLINKY_T 
		|| c == PINKY_T || c == INKY_T || c == CLYDE_T || c == 'R' || c == 'N' 
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_map_line(char *line)
{
	char	*p;
	int		has_tile;

	if (!line)
		return (0);
	p = skip_whitespace(line);
	if (!*p || *p == '\n' || is_cub_prefix(p))
		return (0);
	has_tile = 0;
	while (*p && *p != '\n')
	{
		if (*p != ' ' && *p != '\t')
		{
			if (!is_valid_map_char(*p))
				return (0);
			has_tile = 1;
		}
		p++;
	}
	return (has_tile);
}
