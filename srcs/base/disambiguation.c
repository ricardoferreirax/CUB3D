/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disambiguation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:51:17 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 16:25:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || x >= xtile(map) || y < 0 || y >= ytile(map) || map[y][x] == 'F'
		|| map[y][x] == '1')
		return ;
	if (map[y][x] == 'G')
	{
		map[y][x] = 'F';
		return ;
	}
	if(map[y][x] == 'D')
	{
		map[y][x] = 'F';
		if(x == 0 && map[y][xtile(map) - 1] == 'D')
			flood_fill(map, xtile(map) - 1, y);
		else if (x == xtile(map) - 1 && map[y][0] == 'D')
			flood_fill(map, 0, y);
	}
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	disambiguation(t_point player_spawn, t_map map, t_point coord)
{
	unsigned char	mask;
	int				final;

	flood_fill(map.grid, player_spawn.x, player_spawn.y);
	mask = mask_constructor(&map, &coord, 'F');
	final = find_disamb_sprite(mask);
	return (final);
}
