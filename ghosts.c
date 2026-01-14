/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:48:40 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/12 16:48:59 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

int ft_abs(int n)
{
	if(n < 0)
		return -n;
	return n;
}


//direction vectors
//left 01,00
//right -01,00
//down 00,01
//up 00,-01

//this only is useful to compare distance is it doesn't sqrt(9 the result)
int distance_to_target(t_ghost *ghost, int x, int y)
{
	int result = pow((ghost->pos.tile_pos.x - x) - ghost->target_tile.x, 2) + pow((ghost->pos.tile_pos.y + y) - ghost->target_tile.y, 2);
	return result;
}

t_point chose_next_move(t_ghost *ghost, char **map)
{
	int direction[4][2] = { {0,-1}, {-1, 0}, {0,1}, {1, 0}};
	int i = 0;
	int best = -1;
	int best_dir = -1;
	while(i < 4)
	{
		if(map[ghost->pos.tile_pos.y + direction[i][0]][ghost->pos.tile_pos.x + direction[i][1]] != '1')
		{
			int dist = distance_to_target(ghost, direction[i][0], direction[i][1]);

			if (best == -1 || dist < best)
			{
				best= dist;
				best_dir = i;
			}
		}
		i++;
	}
	t_point dir;
	dir.x = direction[best_dir][0];
	dir.y = direction[best_dir][1];
	return dir;
}
