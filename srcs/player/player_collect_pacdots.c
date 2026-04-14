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

	dx = g->player.pos.tile_pos.x - p->pos.tile_pos.x;
	dy = g->player.pos.tile_pos.y - p->pos.tile_pos.y;
	return ((dx * dx + dy * dy) <= (r * r));
}

bool		player_collect_energizer(t_game *g)
{
	int		i;
	double	pickup_radius;
	bool collected;
	collected = false;


	if (!g || !g->energizers || g->energizer_count <= 0)
		return false;
	pickup_radius = 0.50;
	i = 0;
	while (i < g->energizer_count)
	{
		if (g->energizers[i].active && pacdot_near_player(g, &g->energizers[i], pickup_radius))
		{
			g->energizers[i].active = 0;
			collected = true;
			g->player.collected_dots++;
		}
		i++;
	}
	if(collected)
	{
		i = 0;
		while(i < 4)
		{
			g->ghosts[i].state = FRIGHTENED;
			g->ghosts[i].invalid_dir = (g->ghosts[i].invalid_dir + 2) % 4;
			i++;
		}
		g->timer.frightened_time_start = get_time_us();
	}
	return collected;
}

bool		player_collect_pacdots(t_game *g)
{
	int		i;
	double	pickup_radius;
	bool collected;
	collected = false;


	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return false;
	pickup_radius = 0.50;
	i = 0;
	while (i < g->pacdot_count)
	{
		if (g->pacdots[i].active && pacdot_near_player(g, &g->pacdots[i], pickup_radius))
		{
			g->pacdots[i].active = 0;
			collected = true;
			g->player.collected_dots++;
		}
		i++;
	}
	return collected;
}


static int	player_touching_ghost(t_game *g, t_ghost *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos.tile_pos.x - p->pos.tile_pos.x;
	dy = g->player.pos.tile_pos.y - p->pos.tile_pos.y;
	return ((dx * dx + dy * dy) <= (r * r));
}

int		player_touched_ghost(t_game *g)
{
	int		i;
	double	hit_radius;
	bool hit;
	hit = false;
	int slayer;


	if (!g || !g->pacdots || g->pacdot_count <= 0)
		return false;
	hit_radius = 1;
	i = 0;
	while (i < 4)
	{
		if (g->ghosts[i].name != DISABLED && g->ghosts[i].state != EATEN && player_touching_ghost(g, &g->ghosts[i], hit_radius))
		{
			hit = true;
			slayer = i;
		}
		i++;
	}
	if(!hit)
		return 0;
	return slayer + 1;
}
