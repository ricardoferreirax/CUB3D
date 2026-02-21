/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gate_iteraction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:38:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 21:38:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	gate_in_front(t_game *g)
{
	if (!g)
		return (0);
	if (g->player.target_tile != GATE)
		return (0);
	if (g->player.target_dist > 1.25)
		return (0);
	return (1);
}

static void	gate_toggle(t_game *g)
{
	if (!g)
		return ;
	if (!gate_in_front(g))
		return ;
	if (g->gate_passable)
		g->gate_passable = 0;
	else
		g->gate_passable = 1;
}

void	handle_gate_input(t_game *g)
{
	if (!g)
		return ;
	if (!g->key.e)
		return ;
	if (g->key.e_lock)
		return ;
	g->key.e_lock = 1;
	gate_toggle(g);
}
