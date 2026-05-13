/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collect_pacdots.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:03:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:42:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static int	pacdot_near_player(t_game *g, t_pacdot *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos.tile_pos.x - p->pos.tile_pos.x;
	dy = g->player.pos.tile_pos.y - p->pos.tile_pos.y;
	return ((dx * dx + dy * dy) <= (r * r));
}

static void	set_ghosts_frightened(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->ghosts[i].state != EATEN)
		{
			g->ghosts[i].state = FRIGHTENED;
			g->ghosts[i].invalid_dir = (g->ghosts[i].invalid_dir + 2) % 4;
		}
		i++;
	}
	g->timer.frightened_time_start = get_time_us();
}

bool	player_collect_energizer(t_game *g)
{
	int		i;
	bool	collected;

	collected = false;
	if (!g || !g->energizers || g->energizer_count <= 0)
		return (false);
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active
			&& pacdot_near_player(g, &g->energizers[i], 0.50))
		{
			g->energizers[i].active = 0;
			collected = true;
			g->player.collected_dots++;
		}
		i++;
	}
	if (collected)
		set_ghosts_frightened(g);
	return (collected);
}

bool	player_collect_pacdots(t_game *g)
{
	int		i;
	bool	collected;

	collected = false;
	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return (false);
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active
			&& pacdot_near_player(g, &g->pacdots[i], 0.50))
		{
			g->pacdots[i].active = 0;
			collected = true;
			g->player.collected_dots++;
		}
		i++;
	}
	return (collected);
}
