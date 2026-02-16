/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_energizers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:47:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 05:08:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	energizer_count_map(t_game *g)
{
	int	y;
	int	x;
	int	n;

	y = 0;
	n = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == ENERGIZER)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static void	energizer_fill_map(t_game *g)
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
			if (g->map.grid[y][x] == ENERGIZER)
			{
				g->energizers[i].x = (double)x + 0.5;
				g->energizers[i].y = (double)y + 0.5;
				g->energizers[i].active = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	init_energizers(t_game *g)
{
	int	n;

	if (!g || !g->map.grid)
		return ;
	n = energizer_count_map(g);
	g->energizer_count = n;
	if (n <= 0)
		return ;
	g->energizers = malloc(sizeof(t_pacdot) * n);
	if (!g->energizers)
		exit_game(EXIT_MALLOC, g);
	energizer_fill_map(g);
}
