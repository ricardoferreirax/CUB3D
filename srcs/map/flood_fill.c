/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:57:15 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 16:52:29 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../base/base.h"
#include "../player/player3D.h"
#include "map3D.h"

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
	point.y = 0;
	while (point.y < game->map.height)
	{
		point.x = 0;
		while (point.x < game->map.width)
		{
			if (game->map.grid[point.y][point.x] == ' ')
			{
				if (temp[point.y][point.x] == 'F')
					exit_game(EXIT_MAP, game,
						"Found a void tile that is accessible to the player");
			}
			point.x++;
		}
		point.y++;
	}
	free_2d((void **)temp);
}
