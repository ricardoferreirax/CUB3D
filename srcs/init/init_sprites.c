/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:15:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 17:57:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

static int	count_in_map(t_game *g, char target)
{
	int	y;
	int	x;
	int	n;

	if (!g || !g->map.grid)
		return (0);
	y = 0;
	n = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == target)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static void	fill_from_map(t_game *g, t_pacdot *arr, char target)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == target)
			{
				arr[i].x = (double)x + 0.5;
				arr[i].y = (double)y + 0.5;
				arr[i].active = 1;
				arr[i].eaten = false;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	init_sprite(t_game *g, char target, t_pacdot **arr, int *count)
{
	int	n;

	if (!g || !arr || !count)
		return ;
	*arr = NULL;
	*count = count_in_map(g, target);
	n = *count;
	if (n <= 0)
		return ;
	*arr = malloc(sizeof(t_pacdot) * n);
	if (!*arr)
		exit_game(EXIT_MALLOC, g);
	fill_from_map(g, *arr, target);
}

void	init_sprites(t_game *g)
{
	init_sprite(g, PACDOT, &g->pacdots, &g->pacdot_count);
	init_sprite(g, ENERGIZER, &g->energizers, &g->energizer_count);
	init_ghosts(g);
}
