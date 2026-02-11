/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/14 15:53:35 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

// void init_sprite(t_sprite_ref *sprite, int x, int y, t_point size)
// {
// 	sprite->coord.x = x;
// 	sprite->coord.y = y;
// 	sprite->height = size.y;
// 	sprite->width = size.x;
// }
//
// void init_anim(t_ghost *blinky)
// {
// 	t_point size;
// 	size.x = TILE_SIZE;
// 	size.y = TILE_SIZE;
// }

void init_blinky(t_game *game, t_ghost *blinky)
{ 
	blinky->target_tile = find_c(game->map.grid, 'B');
	blinky->pos.tile_pos = find_c(blinky->mental_map, 'S');
	blinky->pos.pixel_pos.x = blinky->pos.tile_pos.x * 8;
	blinky->pos.pixel_pos.y = blinky->pos.tile_pos.y * 8;
	// init_anim(blinky);
	blinky->invalid_dir = 3;
}

void init_pinky(t_game *game, t_ghost *pinky)
{
	pinky->target_tile = find_c(game->map.grid, 'P');
	pinky->pos.tile_pos = find_c(pinky->mental_map, 'S');
	pinky->pos.pixel_pos.x = pinky->pos.tile_pos.x * 8;
	pinky->pos.pixel_pos.y = pinky->pos.tile_pos.y * 8;
	pinky->invalid_dir = 3;
}

void init_inky(t_game *game, t_ghost *inky)
{
	inky->target_tile = find_c(game->map.grid, 'I');
	inky->pos.tile_pos = find_c(inky->mental_map, 'S');
	inky->pos.pixel_pos.x = inky->pos.tile_pos.x * 8;
	inky->pos.pixel_pos.y = inky->pos.tile_pos.y * 8;
	inky->invalid_dir = 3;
}

void init_clyde(t_game *game, t_ghost *clyde)
{
	clyde->target_tile = find_c(game->map.grid, 'C');
	clyde->pos.tile_pos = find_c(clyde->mental_map, 'S');
	clyde->pos.pixel_pos.x = clyde->pos.tile_pos.x * 8;
	clyde->pos.pixel_pos.y = clyde->pos.tile_pos.y * 8;
	clyde->invalid_dir = 3;

}
