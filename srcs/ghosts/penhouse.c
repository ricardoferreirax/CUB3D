/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   penhouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:32:49 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 10:50:19 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

int	ghost_in_penhouse(t_ghost *ghost, char **map)
{
	t_point	gate;
	int		x;
	int		y;

	if (!ghost || !map)
		return (0);
	gate = find_c(map, GATE);
	if (gate.x < 0 || gate.y < 0)
		return (0);
	x = ghost->pos.pixel_pos.x / TILE_SIZE;
	y = ghost->pos.pixel_pos.y / TILE_SIZE;
	if (x < gate.x - 2 || x > gate.x + 3)
		return (0);
	if (y < gate.y || y > gate.y + 3)
		return (0);
	return (1);
}

bool	can_ghost_exit_penhouse(t_game *game, t_ghost *ghost)
{
	if (ghost->dot_counter < game->player.collected_dots)
		return (true);
	return (false);
}

void	goto_penhouse(t_game *game, t_ghost *ghost)
{
	ghost->target_tile = game->targets.ghost_house;
	ghost->speed_multiplier = 99;
}

int	ghost_penhouse_dance(t_game *game, t_ghost *ghost, t_point gate)
{
	t_double_point	next;
	int				top_px;
	int				bottom_px;
	int				y;

	top_px = (gate.y + 1) * TILE_SIZE + TILE_SIZE / 2;
	bottom_px = (gate.y + 3) * TILE_SIZE + TILE_SIZE / 2;
	y = (int)ghost->pos.pixel_pos.y;
	if (can_ghost_exit_penhouse(game, ghost))
		ghost->invalid_dir = 2;
	else if (y <= top_px)
		ghost->invalid_dir = 0;
	else if (y >= bottom_px)
		ghost->invalid_dir = 2;
	next = continue_travel(game, ghost, 1);
	ghost_set_pixel_pos(ghost, next.x, next.y);
	return (0);
}

bool	is_on_penhouse(t_point ghost_pos, t_point gate_pos)
{
	if (ghost_pos.x / 8 == gate_pos.x && ghost_pos.y / 8 == gate_pos.y)
		return (true);
	return (false);
}
