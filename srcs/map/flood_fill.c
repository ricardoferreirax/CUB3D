/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:57:15 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:44:32 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../base/base.h"
#include "../player/player3D.h"
#include "map3D.h"

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
	if (map[y][x] == 'D')
	{
		map[y][x] = 'F';
		if (x == 0 && map[y][xtile(map) - 1] == 'D')
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

void	map_flood_fill(t_game *game)
{
	char	**temp;
	t_point	spawn;
	t_point	point;

	temp = copy_map(game->map.grid);
	if (!temp)
		exit_game(EXIT_MALLOC, game,
			"Buy More RAM (if you can afford it, brokie :P)");
	spawn = find_player_spawn(game);
	flood_fill(temp, spawn.x, spawn.y);
	point.y = -1;
	while (++point.y < game->map.height)
	{
		point.x = -1;
		while (++point.x < game->map.width)
		{
			if (game->map.grid[point.y][point.x] == ' ')
			{
				if (temp[point.y][point.x] == 'F')
					exit_game(EXIT_MAP, game,
						"Found a void tile that is accessible to the player");
			}
		}
	}
	free_2d((void **)temp);
}
