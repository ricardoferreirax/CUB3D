/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:22:07 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:41:46 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"
#include "../Pac_Struct.h"

void	ghost_info(int i, int *name, char *spawn)
{
	if (i == 0)
	{
		*name = BLINKY;
		*spawn = BLINKY_T;
	}
	else if (i == 1)
	{
		*name = PINKY;
		*spawn = PINKY_T;
	}
	else if (i == 2)
	{
		*name = INKY;
		*spawn = INKY_T;
	}
	else
	{
		*name = CLYDE;
		*spawn = CLYDE_T;
	}
}

t_point	find_spawn(char **map, char ghost)
{
	t_point	gate_pos;

	gate_pos = find_c(map, GATE);
	if (gate_pos.x < 0 || gate_pos.y < 0)
		return (gate_pos);
	if (ghost == BLINKY_T)
	{
		gate_pos.y -= 1;
		return (gate_pos);
	}
	gate_pos.y += 1;
	if (ghost == PINKY_T)
		return (gate_pos);
	if (ghost == INKY_T)
		gate_pos.x += 1;
	if (ghost == CLYDE_T)
		gate_pos.x -= 1;
	return (gate_pos);
}

int	init_dot_counter(t_ghost *gh)
{
	if (gh->name == BLINKY)
	{
		gh->cruiser.is_blinky = 1;
		gh->cruiser.one.enabled = 0;
		gh->cruiser.two.enabled = 0;
	}
	else if (gh->name == PINKY)
	{
		gh->dot_counter = 7;
		gh->cruiser.is_blinky = 0;
	}
	else if (gh->name == INKY)
	{
		gh->dot_counter = 17;
		gh->cruiser.is_blinky = 0;
	}
	else if (gh->name == CLYDE)
	{
		gh->dot_counter = 32;
		gh->cruiser.is_blinky = 0;
	}
	else
		return (-1);
	return (0);
}

const t_lvl_config	g_lvl_config[21] = {
{{0, {0, 20, 80}, {0, 10, 85}}, 75, 50,
	40, 80, 90, 6.0, 100, {7, 20, 7, 20, 5, 20, 5, -1}},
{{0, {0, 30, 90}, {0, 15, 95}}, 85, 55,
	45, 90, 95, 5.0, 300, {7, 20, 7, 20, 5, 1033, 0, -1}},
{{0, {0, 40, 90}, {0, 20, 95}}, 85, 55,
	45, 90, 95, 4.0, 500, {7, 20, 7, 20, 5, 1033, 0, -1}},
{{0, {0, 40, 90}, {0, 20, 95}}, 85, 55,
	45, 90, 95, 3.0, 500, {7, 20, 7, 20, 5, 1033, 0, -1}},
{{0, {0, 40, 100}, {0, 20, 105}}, 95,
	60, 50, 100, 100, 2.0, 700, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 50, 100}, {0, 25, 105}}, 95,
	60, 50, 100, 100, 5.0, 700, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 50, 100}, {0, 25, 105}}, 95,
	60, 50, 100, 100, 2.0, 1000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 50, 100}, {0, 25, 105}}, 95,
	60, 50, 100, 100, 2.0, 1000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 60, 100}, {0, 30, 105}}, 95,
	60, 50, 100, 100, 1.0, 2000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 60, 100}, {0, 30, 105}}, 95,
	60, 50, 100, 100, 5.0, 2000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 60, 100}, {0, 30, 105}}, 95,
	60, 50, 100, 100, 2.0, 3000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 80, 100}, {0, 40, 105}}, 95,
	60, 50, 100, 100, 1.0, 3000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 80, 100}, {0, 40, 105}}, 95,
	60, 50, 100, 100, 1.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 80, 100}, {0, 40, 105}}, 95,
	60, 50, 100, 100, 3.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 100, 100}, {0, 50, 105}}, 95,
	60, 50, 100, 100, 1.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 100, 100}, {0, 50, 105}}, 95,
	60, 50, 100, 100, 1.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 100, 100}, {0, 50, 105}}, 95,
	60, 50, 100, 100, 0.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 100, 100}, {0, 50, 105}}, 95,
	60, 50, 100, 100, 1.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 120, 100}, {0, 60, 105}}, 95,
	60, 50, 100, 100, 0.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 120, 100}, {0, 60, 105}}, 95,
	60, 50, 100, 100, 0.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}},
{{0, {0, 120, 100}, {0, 60, 105}}, 95,
	60, 50, 90, 100, 0.0, 5000, {5, 20, 5, 20, 5, 1003, 0, -1}}
};

void	set_lvl(t_game *game)
{
	int	lvl;
	int	i;

	lvl = game->level - 1;
	if (game->level > 21)
		lvl = 20;
	game->timer.frightened_time = g_lvl_config[lvl].frightened_time;
	game->player.speed_multiplier = g_lvl_config[lvl].pacman_speed;
	game->player.frightened_speed = g_lvl_config[lvl].pacman_frightened_speed;
	game->timer.mode = 0;
	i = -1;
	while (++i < 8)
		game->timer.times[i] = g_lvl_config[lvl].time[i];
	i = -1;
	while (++i < 4)
	{
		game->ghosts[i].cruiser = g_lvl_config[lvl].elroy;
		if (game->ghosts[i].name == BLINKY)
			game->ghosts[i].cruiser.is_blinky = 1;
		game->ghosts[i].speed_multiplier = g_lvl_config[lvl].ghost_speed;
		game->ghosts[i].speed_frightened
			= g_lvl_config[lvl].ghost_frightened_speed;
		game->ghosts[i].speed_tunnel = g_lvl_config[lvl].ghost_tunnel_speed;
	}
}
