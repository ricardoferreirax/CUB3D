/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:38:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 21:15:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	map_is_cub_prefix(char *p)
{
	return (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
		|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2)
		|| *p == 'F' || *p == 'C');
}

static int	map_is_valid_char_in_line(char c)
{
	return (c == '\n' || c == ' ' || c == '\t' || c == WALL || c == OPEN_SPACE
		|| c == PACDOT || c == WRAP_PORTS || c == BLINKY_T || c == PINKY_T 
		|| c == INKY_T || c == CLYDE_T || c == ENERGIZER
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == GATE);
}


int	map_is_map_line(char *line)
{
	char	*p;
	int		has_tile;

	if (!line)
		return (0);
	p = skip_whitespace(line);
	if (!*p || *p == '\n' || map_is_cub_prefix(p))
		return (0);
	has_tile = 0;
	while (*p && *p != '\n')
	{
		if (*p != ' ' && *p != '\t')
		{
			if (!map_is_valid_char_in_line(*p))
				return (0);
			has_tile = 1;
		}
		p++;
	}
	return (has_tile);
}

int	map_is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
