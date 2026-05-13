/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:34:12 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:13:00 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"
#include "../utils/helpers.h"

t_point	pinky_target(t_game *game, int n)
{
	t_point	target;
	int		px;
	int		py;

	px = game->player.pos.tile_pos.x;
	py = game->player.pos.tile_pos.y;
	if (game->player.target_dir.x == 1)
		return ((t_point){px + n, py});
	else if (game->player.target_dir.x == -1)
		return ((t_point){px - n, py});
	else if (game->player.target_dir.y == 1)
		return ((t_point){px, py + n});
	else
		return ((t_point){px - n, py - n});
	return (target);
}

t_point	inky_target(t_game *game)
{
	t_point			pivot;
	t_double_point	blinky;
	t_point			target;
	int				vx;
	int				vy;

	pivot = pinky_target(game, 2);
	blinky = game->ghosts[BLINKY].pos.tile_pos;
	vx = pivot.x - blinky.x;
	vy = pivot.y - blinky.y;
	vx *= 2;
	vy *= 2;
	target.x = blinky.x + vx;
	target.y = blinky.y + vy;
	return (target);
}

t_point	ghost_pos_intile(t_point pos)
{
	return ((t_point){.x = pos.x * 8, .y = pos.y * 8});
}

t_point	chase_player(t_game *game, t_ghost *ghost)
{
	if (ghost->state == EATEN || ghost->state == FRIGHTENED)
		return (ghost->target_tile);
	if (ghost->name == BLINKY)
		return ((t_point){.x = game->player.pos.tile_pos.x,
			.y = game->player.pos.tile_pos.y});
	if (ghost->name == PINKY)
		return (pinky_target(game, 4));
	if (ghost->name == CLYDE)
	{
		if (distance_squared(ghost->pos.tile_pos,
				game->player.pos.tile_pos) >= 8 * TILE_SIZE)
			return ((t_point){.x = game->player.pos.tile_pos.x,
				.y = game->player.pos.tile_pos.y});
		else
			return ((t_point){.x = game->targets.scatter_target[CLYDE].x,
				.y = game->targets.scatter_target[CLYDE].y});
	}
	if (ghost->name == INKY)
		return (inky_target(game));
	return ((t_point){0, 0});
}
