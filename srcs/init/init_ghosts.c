/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/02 09:52:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"
#include "../render/render3D.h"

static void	ghost_info(int i, int *name, char *spawn)
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

// static void	ghost_update_pixel_pos(t_ghost *gh) // guardar pixel_pos para o minimapa 
// {
// 	gh->pos.pixel_pos.x = (gh->pos.tile_pos.x + 0.5) * (double)TILE_SIZE_3D;
// 	gh->pos.pixel_pos.y = (gh->pos.tile_pos.y + 0.5) * (double)TILE_SIZE_3D;
// }

void ghost_sprites(t_game *game, e_ghost ghost)
{
	game->ghosts[ghost].frames.up[0] = game->sprite_sheet.sprites[202];
	game->ghosts[ghost].frames.up[1] = game->sprite_sheet.sprites[203];
	game->ghosts[ghost].frames.left[0] = game->sprite_sheet.sprites[200];
	game->ghosts[ghost].frames.left[1] = game->sprite_sheet.sprites[201];
	game->ghosts[ghost].frames.down[0] = game->sprite_sheet.sprites[198];
	game->ghosts[ghost].frames.down[1] = game->sprite_sheet.sprites[199];
	game->ghosts[ghost].frames.right[0] = game->sprite_sheet.sprites[196];
	game->ghosts[ghost].frames.right[1] = game->sprite_sheet.sprites[197];
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

t_point find_spawn(char **map, char ghost)
{
	t_point gate_pos;
	gate_pos = find_c(map, GATE);
	if(ghost == BLINKY_T)
	{
		gate_pos.y -= 1;
		return gate_pos;
	}
	gate_pos.y += 1;
	if(ghost == PINKY_T)
		return gate_pos;
	if(ghost == INKY_T)
		gate_pos.x += 1;
	if(ghost == CLYDE_T) 
		gate_pos.x -= 1;
	return gate_pos;
}

static int	init_one_ghost(t_game *g, t_ghost *gh, char target_char, int is_death)
{
	t_point	target_point;
	t_point spawn_point;

	if(!is_death)
		gh->mental_map = copy_map(g->map.grid);
	if (!gh->mental_map && !is_death)
		exit_game(EXIT_MALLOC, g, "init_one_ghost() was unable to copy map");
	target_point = find_c(g->map.grid, target_char);
	spawn_point = find_spawn(g->map.grid, target_char);
	if (target_point.x < 0 || target_point.y < 0 || spawn_point.x < 0 || spawn_point.y < 0)
		return -1;
	if(gh->name == BLINKY && !is_death)
		g->targets.ghost_house = spawn_point;
	g->targets.scatter_target[gh->name] = spawn_point;
	gh->pos.tile_pos.x = (double)spawn_point.x+ 0.5; // posiciona o ghost no centro do spawn tile no eixo x
	gh->pos.tile_pos.y = (double)spawn_point.y + 0.5; // posiciona o ghost no centro do spawn tile no eixo y
	gh->pos.pixel_pos.x = spawn_point.x * TILE_SIZE + TILE_SIZE / 2; // converte o spawn tile para pixels e centra o fanstasma no tile no eixo x
	gh->pos.pixel_pos.y = spawn_point.y * TILE_SIZE + TILE_SIZE / 2; // converte o spawn tile para pixels e centra o fanstasma no tile no eixo y
	gh->invalid_dir = -1;
	gh->target_tile = target_point;
	if(is_death)
		return 0;
	ghost_sprites(g, gh->name);
	ghost_color(gh);
	return 0;
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
		if(init_one_ghost(g, &g->ghosts[i], spawn, is_death) || g->mode == MODE_CUBE)
			g->ghosts[i].name = DISABLED;
		i++;
	}
}
