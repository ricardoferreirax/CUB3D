/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:11:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:21:48 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/helpers.h"
#include "ghosts.h"

void	update_cruise_elroy(t_game *game, t_ghost *ghost)
{
	int	dots_left;

	dots_left = ft_abs(game->player.collected_dots - game->pacdot_count);
	if (!ghost->cruiser.two.enabled
		&& dots_left <= ghost->cruiser.two.dots_left)
	{
		if (game->debug_mode)
			ft_printf("Blinky is Elroy level 2\n");
		ghost->speed_multiplier = ghost->cruiser.two.speed_multiplier;
		ghost->cruiser.two.enabled = true;
	}
	else if (!ghost->cruiser.one.enabled
		&& dots_left <= ghost->cruiser.one.dots_left)
	{
		if (game->debug_mode)
			ft_printf("Blinky is Elroy level 1\n");
		ghost->speed_multiplier = ghost->cruiser.one.speed_multiplier;
		ghost->cruiser.one.enabled = true;
	}
}

void	update_target(t_game *game, t_ghost *ghost)
{
	if (ghost->state == EATEN)
		goto_penhouse(game, ghost);
	if (ghost->state == SCATTER && (!ghost->cruiser.is_blinky
			|| !(ghost->cruiser.one.enabled || ghost->cruiser.two.enabled)))
		ghost->target_tile = game->targets.scatter_target[ghost->name];
	if (ghost->state == CHASE || (ghost->cruiser.is_blinky
			&& (ghost->cruiser.one.enabled || ghost->cruiser.two.enabled)))
		ghost->target_tile = chase_player(game, ghost);
	if (ghost->cruiser.is_blinky)
		update_cruise_elroy(game, ghost);
}

int	update_ghost(t_game *game, t_ghost *ghost)
{
	t_double_point	next;

	if (!ghost)
		return (-1);
	if (ghost->name == DISABLED || game->mode == MODE_CUBE)
		return (0);
	if (ghost_in_penhouse(ghost, ghost->mental_map.grid))
		return (ghost_penhouse_dance(game, ghost, find_c(ghost->mental_map.grid,
					'G')));
	if (ghost->state == FRIGHTENED && get_time_us()
		- game->timer.frightened_time_start > (long)(game->timer.frightened_time
		* 1000000.0))
	{
		ghost->state = game->global_state;
		ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
	}
	if (ghost->state == EATEN && is_on_penhouse(ghost->pos.pixel_pos,
			game->targets.ghost_house))
	{
		ghost->state = game->global_state;
		ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
	}
	if (ghost->pos.pixel_pos.x % TILE_SIZE != TILE_SIZE / 2
		|| ghost->pos.pixel_pos.y % TILE_SIZE != TILE_SIZE / 2)
	{
		update_target(game, ghost);
		next = continue_travel(game, ghost, 0);
		ghost_set_pixel_pos(ghost, next.x, next.y);
		return (0);
	}
	ghost->invalid_dir = chose_next_move(game, ghost, &ghost->mental_map);
	if (ghost->invalid_dir == -1)
		return (-1);
	return (0);
}
