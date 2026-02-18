/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_eat_pacdots.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:03:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 21:04:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static int	pacdot_in_range(t_game *g, t_pacdot *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos_x - p->x;
	dy = g->player.pos_y - p->y;
	return ((dx * dx + dy * dy) <= (r * r));
}

void		player_eat_pacdots(t_game *g)
{
	int		i;
	double	r;

	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return ;

	/*
	 * Raio de “comer” em unidades do mundo (tile = 1.0).
	 * 0.20–0.35 costuma ficar bom.
	 * Começa em 0.30.
	 */
	r = 0.30;

	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active && pacdot_in_range(g, &g->pacdots[i], r))
			g->pacdots[i].active = 0;
		i++;
	}
}
