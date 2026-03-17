/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_eat_pacdots.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:03:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:25:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static int	pacdot_near_player(t_game *g, t_pacdot *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos.tile_pos.x - p->x;
	dy = g->player.pos.tile_pos.y - p->y;
	return ((dx * dx + dy * dy) <= (r * r));
}

void		player_collect_pacdots(t_game *g)
{
	int		i;
	double	pickup_radius;

	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return ;
	pickup_radius = 0.30;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active && pacdot_near_player(g, &g->pacdots[i], pickup_radius))
			g->pacdots[i].active = 0;
		i++;
	}
}
