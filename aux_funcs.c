/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:42:39 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/12 13:53:02 by pfreire-         ###   ########.fr       */
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

char which_ghost(t_ghost *ghost)
{
	if(ghost->name == BLINKY)
		return 'L';
	if(ghost->name == PINKY)
		return 'I';
	if(ghost->name == INKY)
		return 'K';
	if(ghost->name == CLYDE)
		return 'Y';
}

void move(char** map, t_ghost *ghost, int dx, int dy)
{
	char ghost_to_move = which_ghost(ghost);

	int new_posx = ghost->pos.tile_pos.x + dx;
	int new_posy = ghost->pos.tile_pos.y + dy;
	map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = '0';
	if(ghost->is_steping_on_pacdot)
	{ 
		if(ghost->is_steping_on_pacdot > 0)
			map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = 'D';
		if (ghost->is_steping_on_pacdot > 1)
			map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = 'E';
		ghost->is_steping_on_pacdot = 0;
	}
	if(map[new_posy][new_posx] != '0')
	{
		if(map[new_posy][new_posx] == 'D')
			ghost->is_steping_on_pacdot = 1;
		else if(map[new_posy][new_posx] == 'E')
			ghost->is_steping_on_pacdot = 2;
	}
	map[new_posy][new_posx] = ghost_to_move;
}
