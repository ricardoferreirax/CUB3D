/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:38:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/10 22:42:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"
#include "../textures/textures3D.h"

static int	map_cube_mode_prefix(char *p)
{
	if (!p)
		return (0);
	if (!ft_strncmp(p, "NO", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "SO", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "WE", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "EA", 2) && is_whitespace(p[2]))
		return (1);
	if (*p == 'F' && is_whitespace(p[1]))
		return (1);
	if (*p == 'C' && is_whitespace(p[1]))
		return (1);
	return (0);
}

static int	map_pacman_mode_prefix(char *p)
{
	if (!p)
		return (0);
	if (!ft_strncmp(p, "PD", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "EN", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "BL", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "PI", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "IN", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "CL", 2) && is_whitespace(p[2]))
		return (1);
	if (!ft_strncmp(p, "GC", 2) && is_whitespace(p[2]))
		return (1);
	return (0);
}

static int	map_is_cub_prefix(char *p)
{
	if (map_cube_mode_prefix(p))
		return (1);
	if (map_pacman_mode_prefix(p))
		return (1);
	return (0);
}

bool target_tile(char c)
{
	if(c == 'L' || c == 'V' || c == 'K' || c == 'Y')
		return true;
	return false;
}

static int	map_is_valid_char_in_line(char c, t_mode mode)
{
	if (c == '\n' || c == ' ' || c == '\t'
		|| c == WALL || c == OPEN_SPACE
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (mode == MODE_PACMAN)
	{
		if (c == PACDOT || c == WRAP_PORTS || c == ENERGIZER
			|| c == BLINKY_T || c == PINKY_T || c == INKY_T || c == CLYDE_T
			|| c == GATE || c == PLAYER || c == 'M')
			return (1);
	}
	return (0);
}

int	map_is_map_line(t_game *g, char *line)
{
	char	*p;
	int		has_tile;

	if (!line || !g)
		return (0);
	p = skip_whitespace(line);
	if (!*p || *p == '\n' || map_is_cub_prefix(p))
		return (0);
	has_tile = 0;
	while (*p && *p != '\n')
	{
		if (*p != ' ' && *p != '\t')
		{
			if (!map_is_valid_char_in_line(*p, g->mode))
				return (0);
			has_tile = 1;
		}
		p++;
	}
	return (has_tile);
}
