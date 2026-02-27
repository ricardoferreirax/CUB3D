/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/27 22:02:12 by rmedeiro         ###   ########.fr       */
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
	copy = ft_calloc(sizeof(char *), h + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		copy[i] = ft_calloc(sizeof(char), ft_strlen(map[i]) + 1);
		if (!copy[i])
			return (free_copy_partial(copy, i), NULL);
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'M')
				copy[i][j] = '1';
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

static void	set_ghost_name(t_ghost *gh, int i)
{
	if (i == 0)
		gh->name = BLINKY;
	else if (i == 1)
		gh->name = PINKY;
	else if (i == 2)
		gh->name = INKY;
	else
		gh->name = CLYDE;
}

static char	ghost_spawn_char(t_ghost *gh)
{
	if (gh->name == BLINKY)
		return ('B');
	if (gh->name == PINKY)
		return ('P');
	if (gh->name == INKY)
		return ('I');
	if (gh->name == CLYDE)
		return ('C');
	return ('S');
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

static void	init_one_ghost(t_game *g, t_ghost *gh)
{
	t_point	p;

	gh->mental_map = copy_map(g->map.grid);
	if (!gh->mental_map)
		exit_game(EXIT_MALLOC, g);
	p = find_c(g->map.grid, ghost_spawn_char(gh));
	if (p.x < 0 || p.y < 0)
		p = find_c(g->map.grid, 'S');
	if (p.x < 0 || p.y < 0)
		exit_game(EXIT_MAP, g);
	gh->pos.tile_pos.x = (double)p.x;
	gh->pos.tile_pos.y = (double)p.y;
	gh->target_tile = p;
	gh->invalid_dir = 3;
}

void	init_ghosts(t_game *g)
{
	int	i;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	i = 0;
	while (i < 4)
	{
		ft_bzero(&g->ghosts[i], sizeof(t_ghost));
		set_ghost_name(&g->ghosts[i], i);
		init_one_ghost(g, &g->ghosts[i]);
		i++;
	}
}

// static int ghost_tile_x(t_ghost *gh)
// {
//     return ((int)gh->pos.tile_pos.x);
// }

// static int ghost_tile_y(t_ghost *gh)
// {
//     return ((int)gh->pos.tile_pos.y);
// }
