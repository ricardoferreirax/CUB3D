/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:41:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/12 18:41:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	map_tile_type(char t, int tile_type)
{
	if (tile_type == TILE_WALL)
		return (t == WALL || t == 'M');
	if (tile_type == TILE_VOID)
		return (t == VOID);
	if (tile_type == TILE_SOLID)
		return (t == WALL || t == 'M' || t == GATE);
	if (tile_type == TILE_WALKABLE)
	{
		return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
			|| t == WRAP_PORTS || t == 'N'
			|| t == 'S' || t == 'E' || t == 'W');
	}
	return (0);
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
