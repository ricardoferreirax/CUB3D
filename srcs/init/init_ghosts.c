/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/26 22:59:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

static void	ghost_set(t_game *g, e_ghost who, int x, int y)
{
	g->ghosts[who].name = who;
	g->ghosts[who].pos.tile_pos.x = (double)x + 0.5;
	g->ghosts[who].pos.tile_pos.y = (double)y + 0.5;
}

static void	ghost_fill_from_map(t_game *g)
{
	int		x;
	int		y;
	char	t;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			t = map_get_tile(g, y, x);
			if (t == BLINKY_T)
				ghost_set(g, BLINKY, x, y);
			else if (t == PINKY_T)
				ghost_set(g, PINKY, x, y);
			else if (t == INKY_T)
				ghost_set(g, INKY, x, y);
			else if (t == CLYDE_T)
				ghost_set(g, CLYDE, x, y);
			if (t == BLINKY_T || t == PINKY_T
				|| t == INKY_T || t == CLYDE_T)
				g->map.grid[y][x] = OPEN_SPACE;
		}
	}
}

void	init_ghosts(t_game *g)
{
	if (!g || !g->map.grid)
		return ;
	ghost_fill_from_map(g);
}

// static int ghost_tile_x(t_ghost *gh)
// {
//     return ((int)gh->pos.tile_pos.x);
// }

// static int ghost_tile_y(t_ghost *gh)
// {
//     return ((int)gh->pos.tile_pos.y);
// }
