/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:40:06 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../ghosts/ghosts.h"
#include "../render/render3D.h"
#include "initializer.h"
#include "../utils/helpers.h"

static int	init_ghots_pos(t_game *g, t_ghost *gh, char tc, int is_death)
{
	t_point	target_point;
	t_point	spawn_point;

	target_point = find_c(g->map.grid, tc);
	spawn_point = find_spawn(g->map.grid, tc);
	if (target_point.x < 0 || target_point.y < 0 || spawn_point.x < 0
		|| spawn_point.y < 0)
		return (-1);
	g->targets.scatter_target[gh->name] = target_point;
	gh->pos.tile_pos.x = (double)spawn_point.x + 0.5;
	gh->pos.tile_pos.y = (double)spawn_point.y + 0.5;
	gh->pos.pixel_pos.x = spawn_point.x * TILE_SIZE + TILE_SIZE / 2;
	gh->pos.pixel_pos.y = spawn_point.y * TILE_SIZE + TILE_SIZE / 2;
	gh->invalid_dir = 3;
	gh->target_tile = target_point;
	gh->state = SCATTER;
	if (gh->name == BLINKY && !is_death)
		g->targets.ghost_house = spawn_point;
	return (0);
}

static int	init_one_ghost(t_game *g, t_ghost *gh, char target_char,
		int is_death)
{
	if (g->mode == MODE_CUBE)
		return (-1);
	if (!is_death)
	{
		gh->mental_map.grid = copy_map(g->map.grid);
		gh->mental_map.height = ytile(gh->mental_map.grid);
		gh->mental_map.width = xtile(gh->mental_map.grid);
	}
	if (!gh->mental_map.grid && !is_death)
		exit_game(EXIT_MALLOC, g, "init_one_ghost() was unable to copy map");
	if (init_ghots_pos(g, gh, target_char, is_death))
		return (-1);
	if (init_dot_counter(gh))
		return (-1);
	if (is_death)
		return (0);
	ghost_sprites(g, gh->name);
	ghost_color(gh);
	return (0);
}

void	init_ghosts(t_game *g, int is_death)
{
	int		i;
	int		name;
	char	spawn;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "init_ghosts() has not found a valid pointer");
	i = 0;
	while (i < 4)
	{
		ghost_info(i, &name, &spawn);
		g->ghosts[i].name = name;
		if (init_one_ghost(g, &g->ghosts[i], spawn, is_death)
			|| g->mode == MODE_CUBE)
		{
			if (g->debug_mode)
				annouce_disabled(i);
			g->ghosts[i].name = DISABLED;
		}
		i++;
	}
}
