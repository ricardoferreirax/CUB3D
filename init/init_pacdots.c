/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pacdots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:47:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/18 21:03:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	pacdot_count_map(t_game *g)
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
			if (g->map.grid[y][x] == PACDOT)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static void	pacdot_fill_from_map(t_game *g)
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
			if (g->map.grid[y][x] == PACDOT)
			{
				g->pacdots[i].x = (double)x + 0.5;
				g->pacdots[i].y = (double)y + 0.5;
				g->pacdots[i].active = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	init_pacdots(t_game *g)
{
	int	n;

	if (!g || !g->map.grid)
		return ;
	n = pacdot_count_map(g);
	g->pacdot_count = n;
	if (n <= 0)
		return ;
	g->pacdots = malloc(sizeof(t_pacdot) * n);
	if (!g->pacdots)
		exit_game(EXIT_MALLOC, g);
	pacdot_fill_from_map(g);
}
