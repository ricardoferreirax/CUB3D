/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/14 16:08:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

void init_null(t_game *game)
{
	// game->win = NULL;
	game->ghost = NULL;
	game->dot = NULL;
	// game->player = NULL;
}


void init_ghost(t_game *game, t_ghost *ghost)
{
	ghost->is_steping_on_pacdot = 0;
	ghost->mental_map = copy_map(game->map);
	if(ghost->name == BLINKY)
		init_blinky(game, ghost);
	if(ghost->name == PINKY)
		init_pinky(game, ghost);
	if(ghost->name == INKY)
		init_inky(game, ghost);
	if(ghost->name == CLYDE)
		init_clyde(game, ghost);
}

void init_game(t_game *game)
{
	// init_null(game);
	// init_window(game);
	game->ghost = malloc(sizeof(t_ghost) * 4);
	game->ghost[0].name = BLINKY;
	game->ghost[1].name = PINKY;
	game->ghost[2].name = INKY;
	game->ghost[3].name = CLYDE;
	int i = -1;
	while (++i < 4)
		init_ghost(game, &game->ghost[i]);
}
