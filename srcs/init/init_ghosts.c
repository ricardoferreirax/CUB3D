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

static void	ghost_update_pixel_pos(t_ghost *gh) // guardar pixel_pos para o minimapa 
{
	gh->pos.pixel_pos.x = (gh->pos.tile_pos.x + 0.5) * (double)TILE_SIZE;
	gh->pos.pixel_pos.y = (gh->pos.tile_pos.y + 0.5) * (double)TILE_SIZE;
}

static void	init_one_ghost(t_game *g, t_ghost *gh, char spawn_char)
{
	t_point	p;

	gh->mental_map = copy_map(g->map.grid);
	if (!gh->mental_map)
		exit_game(EXIT_MALLOC, g);
	p = find_c(g->map.grid, spawn_char);
	if (p.x < 0 || p.y < 0)
		exit_game(EXIT_MAP, g);
	gh->pos.tile_pos.x = (double)p.x;
	gh->pos.tile_pos.y = (double)p.y;
	ghost_update_pixel_pos(gh);
	gh->invalid_dir = -1;
	gh->target_tile = p;
}

void	init_ghosts(t_game *g)
{
	int		i;
	int		name;
	char	spawn;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	i = 0;
	while (i < 4)
	{
		ghost_info(i, &name, &spawn);
		ft_bzero(&g->ghosts[i], sizeof(t_ghost));
		g->ghosts[i].name = name;
		init_one_ghost(g, &g->ghosts[i], spawn);
		i++;
	}
}
