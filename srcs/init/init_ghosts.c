/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/27 22:24:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

static void	free_copy_partial(char **copy, int rows_done)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < rows_done)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

char	**copy_map(char **map)
{
	char	**copy;
	int		i;
	int		j;
	int		h;

	h = ytile(map);
	copy = ft_calloc((size_t)h + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		copy[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(char));
		if (!copy[i])
			return (free_copy_partial(copy, i), NULL);
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'M')
				copy[i][j] = WALL;
			else
				copy[i][j] = map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_point	find_c(char **map, char c)
{
	t_point	cord;

	cord.y = 0;
	while (map && map[cord.y])
	{
		cord.x = 0;
		while (map[cord.y][cord.x])
		{
			if (map[cord.y][cord.x] == c)
				return (cord);
			cord.x++;
		}
		cord.y++;
	}
	cord.y = -1;
	cord.x = -1;
	return (cord);
}

static void	ghost_update_pixel_pos(t_ghost *gh)
{
	gh->pos.pixel_pos.x = (gh->pos.tile_pos.x + 0.5) * (double)TILE_SIZE;
	gh->pos.pixel_pos.y = (gh->pos.tile_pos.y + 0.5) * (double)TILE_SIZE;
}

static void	init_one_ghost_simple(t_game *g, t_ghost *gh, char spawn_char)
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
	gh->invalid_dir = 3;
	gh->target_tile = p;
}

void	init_ghosts(t_game *g)
{
	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	ft_bzero(&g->ghosts[0], sizeof(t_ghost));
	g->ghosts[0].name = BLINKY;
	init_one_ghost_simple(g, &g->ghosts[0], BLINKY_T);
	ft_bzero(&g->ghosts[1], sizeof(t_ghost));
	g->ghosts[1].name = PINKY;
	init_one_ghost_simple(g, &g->ghosts[1], PINKY_T);
	ft_bzero(&g->ghosts[2], sizeof(t_ghost));
	g->ghosts[2].name = INKY;
	init_one_ghost_simple(g, &g->ghosts[2], INKY_T);
	ft_bzero(&g->ghosts[3], sizeof(t_ghost));
	g->ghosts[3].name = CLYDE;
	init_one_ghost_simple(g, &g->ghosts[3], CLYDE_T);
}
