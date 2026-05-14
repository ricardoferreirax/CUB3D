/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:57:15 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/14 17:58:39 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../base/base.h"
#include "../player/player3D.h"
#include "map3D.h"

static void	check_flood_void(t_game *game, char **temp)
{
	t_point	point;

	point.y = 0;
	while (point.y < game->map.height)
	{
		point.x = 0;
		while (point.x < game->map.width)
		{
			if (game->map.grid[point.y][point.x] == ' '
				&& temp[point.y][point.x] == 'F')
			{
				free_2d((void **)temp);
				exit_game(EXIT_MAP, game, "Found a void tile!");
			}
			point.x++;
		}
		point.y++;
	}
}

void	map_flood_fill(t_game *game)
{
	char	**temp;
	t_point	spawn;

	spawn = find_player_spawn(game);
	temp = copy_map(game->map.grid);
	if (!temp)
		exit_game(EXIT_MALLOC, game,
			"Buy More RAM (if you can afford it, brokie :P)");
	flood_fill(temp, spawn.x, spawn.y);
	check_flood_void(game, temp);
	free_2d((void **)temp);
}
