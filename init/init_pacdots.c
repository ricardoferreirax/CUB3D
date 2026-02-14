/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pacdots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:47:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/13 22:58:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	pac_count(t_game *g)
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
			if (g->map.grid[y][x] == '.')
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static void	pac_fill(t_game *g)
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
			if (g->map.grid[y][x] == '.')
			{
				g->pac.dots[i].x = (double)x + 0.5;
				g->pac.dots[i].y = (double)y + 0.5;
				g->pac.dots[i].active = 1;
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

	if (!g) return;
	if (!g->map.grid) return;

	n = pac_count(g);
	g->pac.count = n;
	if (n <= 0) return;

	g->pac.dots = malloc(sizeof(t_pacdot) * n);
	if (!g->pac.dots) exit_game(EXIT_MALLOC, g);

	pac_fill(g);
}

