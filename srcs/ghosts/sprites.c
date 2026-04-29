/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:22:45 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:37:30 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

void ghost_sprites(t_game *game, e_ghost ghost)
{
	game->ghosts[ghost].frames.up[0] = game->sprite_sheet.sprites[202];
	game->ghosts[ghost].frames.up[1] = game->sprite_sheet.sprites[203];
	game->ghosts[ghost].frames.up[2] = game->sprite_sheet.sprites[209];
	game->ghosts[ghost].frames.left[0] = game->sprite_sheet.sprites[200];
	game->ghosts[ghost].frames.left[1] = game->sprite_sheet.sprites[201];
	game->ghosts[ghost].frames.left[2] = game->sprite_sheet.sprites[208];
	game->ghosts[ghost].frames.down[0] = game->sprite_sheet.sprites[198];
	game->ghosts[ghost].frames.down[1] = game->sprite_sheet.sprites[199];
	game->ghosts[ghost].frames.down[2] = game->sprite_sheet.sprites[207];
	game->ghosts[ghost].frames.right[0] = game->sprite_sheet.sprites[196];
	game->ghosts[ghost].frames.right[1] = game->sprite_sheet.sprites[197];
	game->ghosts[ghost].frames.right[2] = game->sprite_sheet.sprites[206];
	game->ghosts[ghost].frames.scared[0] = game->sprite_sheet.sprites[246];
	game->ghosts[ghost].frames.scared[1] = game->sprite_sheet.sprites[247];
	if(game->ghosts[ghost].name == BLINKY)
	{
		game->ghosts[ghost].frames.up[3] = game->sprite_sheet.sprites[213];
		game->ghosts[ghost].frames.left[3] = game->sprite_sheet.sprites[212];
		game->ghosts[ghost].frames.down[3] = game->sprite_sheet.sprites[211];
		game->ghosts[ghost].frames.right[3] = game->sprite_sheet.sprites[210];
	}
}

void apply_new_pallete(t_point pallet_coord, t_sprite_ref *sprite)
{
	if(!sprite)
		return;
	sprite->coord.x += pallet_coord.x * 200;
	sprite->coord.y += pallet_coord.y * 186;
}

void change_pallete(t_point pallet_coord, t_anim *frames)
{
	apply_new_pallete(pallet_coord, &frames->left[0]);
	apply_new_pallete(pallet_coord, &frames->left[1]);
	apply_new_pallete(pallet_coord, &frames->left[2]);
	apply_new_pallete(pallet_coord, &frames->right[0]);
	apply_new_pallete(pallet_coord, &frames->right[1]);
	apply_new_pallete(pallet_coord, &frames->right[2]);
	apply_new_pallete(pallet_coord, &frames->up[0]);
	apply_new_pallete(pallet_coord, &frames->up[1]);
	apply_new_pallete(pallet_coord, &frames->up[2]);
	apply_new_pallete(pallet_coord, &frames->down[0]);
	apply_new_pallete(pallet_coord, &frames->down[1]);
	apply_new_pallete(pallet_coord, &frames->down[2]);
	int i = 0;
	while(i < 12)
	{
		apply_new_pallete(pallet_coord, &frames->death[i]);
		i++;
	}
}

void ghost_color(t_ghost *ghost)
{
	if (ghost->name == BLINKY)
		return;
	else if(ghost->name == PINKY)
			change_pallete((t_point){.x = 1, .y= 0}, &ghost->frames);
	else if(ghost->name == INKY)
			change_pallete((t_point){.x = 2, .y= 0}, &ghost->frames);
	else if(ghost->name == CLYDE)
			change_pallete((t_point){.x = 3, .y= 0}, &ghost->frames);
}

