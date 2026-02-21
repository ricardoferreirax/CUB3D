/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/21 23:44:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

/* void init_ghost(t_game *game, t_ghost *ghost)
{
	ghost->is_steping_on_pacdot = 0;
	ghost->mental_map = copy_map(game->map.grid);
	ghost->state = SCATTER;
	if (ghost->name == BLINKY)
		init_blinky(game, ghost);
	if (ghost->name == PINKY)
		init_pinky(game, ghost);
	if (ghost->name == INKY)
		init_inky(game, ghost);
	if (ghost->name == CLYDE)
		init_clyde(game, ghost);
}

void	init_ghosts(t_game *game)
{
	int	i;

	game->ghost = malloc(sizeof(t_ghost) * 4);
	i = -1;
	while (++i < 4)
		init_ghost(game, &game->ghost[i]);
} */
