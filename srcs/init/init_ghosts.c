/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:49:10 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../ghosts/ghosts.h"
#include "../render/render3D.h"
#include "initializer.h"

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

static int	init_one_ghost(t_game *g, t_ghost *gh, char target_char,
		int is_death)
{
	t_point	target_point;
	t_point	spawn_point;

	if (g->mode == MODE_CUBE)
		return (-1);
	if (!is_death)
		gh->mental_map = copy_map(g->map.grid);
	if (!gh->mental_map && !is_death)
		exit_game(EXIT_MALLOC, g, "init_one_ghost() was unable to copy map");
	target_point = find_c(g->map.grid, target_char);
	spawn_point = find_spawn(g->map.grid, target_char);
	if (target_point.x < 0 || target_point.y < 0 || spawn_point.x < 0
		|| spawn_point.y < 0)
		return (-1);
	if (gh->name == BLINKY && !is_death)
		g->targets.ghost_house = spawn_point;
	g->targets.scatter_target[gh->name] = target_point;
	gh->pos.tile_pos.x = (double)spawn_point.x + 0.5;               
		// posiciona o ghost no centro do spawn tile no eixo x
	gh->pos.tile_pos.y = (double)spawn_point.y + 0.5;               
		// posiciona o ghost no centro do spawn tile no eixo y
	gh->pos.pixel_pos.x = spawn_point.x * TILE_SIZE + TILE_SIZE / 2;
		// converte o spawn tile para pixels e centra o fanstasma no tile no eixo x
	gh->pos.pixel_pos.y = spawn_point.y * TILE_SIZE + TILE_SIZE / 2;
		// converte o spawn tile para pixels e centra o fanstasma no tile no eixo y
	gh->invalid_dir = 3;
	gh->target_tile = target_point;
	gh->state = SCATTER;
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
	if (is_death)
		return (0);
	ghost_sprites(g, gh->name);
	ghost_color(gh);
	return (0);
}

void	annouce_disabled(int i)
{
	if (i == 0)
		ft_printf("Blinky was disabled\n");
	if (i == 1)
		ft_printf("Pinky was disabled\n");
	if (i == 2)
		ft_printf("Inky was disabled\n");
	if (i == 3)
		ft_printf("ClydE was disabled\n");
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
