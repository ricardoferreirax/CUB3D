/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/16 22:26:47 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	ghost_set(t_game *g, e_ghost who, int x, int y)
{
	g->ghosts[who].name = who;
	g->ghosts[who].sprite_x = (double)x + 0.5;
	g->ghosts[who].sprite_y = (double)y + 0.5;
	g->ghosts[who].pos.tile_pos.x = x;
	g->ghosts[who].pos.tile_pos.y = y;
}

void	init_ghosts(t_game *g)
{
	int		x;
	int		y;
	char	t;

	if (!g || !g->map.grid)
		return ;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
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
			if (t == BLINKY_T || t == PINKY_T || t == INKY_T || t == CLYDE_T)
				g->map.grid[y][x] = OPEN_SPACE;
			x++;
		}
		y++;
	}
}



/* void init_blinky(t_game *game, t_ghost *blinky)
{
	blinky->target_tile = find_c(game->map.grid, 'B');
	blinky->pos.tile_pos = find_c(blinky->mental_map, 'S');
	blinky->invalid_dir = 3;
}

void init_pinky(t_game *game, t_ghost *pinky)
{
	pinky->target_tile = find_c(game->map.grid, 'P');
	pinky->pos.tile_pos = find_c(pinky->mental_map, 'S');
	pinky->invalid_dir = 3;
}

void init_inky(t_game *game, t_ghost *inky)
{
	inky->target_tile = find_c(game->map.grid, 'I');
	inky->pos.tile_pos = find_c(inky->mental_map, 'S');
	inky->invalid_dir = 3;
}

void init_clyde(t_game *game, t_ghost *clyde)
{
	clyde->target_tile = find_c(game->map.grid, 'C');
	clyde->pos.tile_pos = find_c(clyde->mental_map, 'S');
	clyde->invalid_dir = 3;
} */
