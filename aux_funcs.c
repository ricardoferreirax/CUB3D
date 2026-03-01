/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:42:39 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/01 21:19:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

int xtile(char **map)
{
	int i = 0;
	int total = 0;
	while(map && map[i])
	{
		if(total < (int)ft_strlen(map[i]))
			total = ft_strlen(map[i]);
		i++;
	}
	return total;
}

int ytile(char **map)
{
	int i = 0;
	while(map && map[i])
		i++;
	return i;
}

// char which_ghost(t_ghost *ghost)
// {
// 	if(ghost->name == BLINKY)
// 		return 'L';
// 	if(ghost->name == PINKY)
// 		return 'I';
// 	if(ghost->name == INKY)
// 		return 'K';
// 	if(ghost->name == CLYDE)
// 		return 'Y';
// 	return '?';
// }

// void init_blinky(t_game *game, t_ghost *blinky)
// {
// 	blinky->target_tile = find_c(game->map.grid, 'B');
// 	blinky->pos.tile_pos = find_c(blinky->mental_map, 'S');
// 	blinky->invalid_dir = 3;
// }

// void init_pinky(t_game *game, t_ghost *pinky)
// {
// 	pinky->target_tile = find_c(game->map.grid, 'P');
// 	pinky->pos.tile_pos = find_c(pinky->mental_map, 'S');
// 	pinky->invalid_dir = 3;
// }

// void init_inky(t_game *game, t_ghost *inky)
// {
// 	inky->target_tile = find_c(game->map.grid, 'I');
// 	inky->pos.tile_pos = find_c(inky->mental_map, 'S');
// 	inky->invalid_dir = 3;
// }

// void init_clyde(t_game *game, t_ghost *clyde)
// {
// 	clyde->target_tile = find_c(game->map.grid, 'C');
// 	clyde->pos.tile_pos = find_c(clyde->mental_map, 'S');
// 	clyde->invalid_dir = 3;
// }