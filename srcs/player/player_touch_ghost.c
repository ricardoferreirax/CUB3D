/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_touch_ghost.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 15:42:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:42:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static int	player_touching_ghost(t_game *g, t_ghost *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos.tile_pos.x - p->pos.tile_pos.x;
	dy = g->player.pos.tile_pos.y - p->pos.tile_pos.y;
	return ((dx * dx + dy * dy) <= (r * r));
}

int	player_touched_ghost(t_game *g)
{
	int	i;
	int	slayer;

	if (!g)
		return (0);
	i = 0;
	slayer = -1;
	while (i < 4)
	{
		if (g->ghosts[i].name != DISABLED && g->ghosts[i].state != EATEN
			&& player_touching_ghost(g, &g->ghosts[i], 1))
			slayer = i;
		i++;
	}
	if (slayer == -1)
		return (0);
	return (slayer + 1);
}
