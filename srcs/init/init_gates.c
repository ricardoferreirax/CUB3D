/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gates.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:48:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 21:51:14 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"

#include "../Pac_Struct.h"

static int	gate_count_map(t_game *g)
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
			if (g->map.grid[y][x] == GATE)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static void	gate_fill_from_map(t_game *g)
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
			if (g->map.grid[y][x] == GATE)
			{
				g->gates[i].x = (double)x + 0.5;
				g->gates[i].y = (double)y + 0.5;
				g->gates[i].active = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	init_gates(t_game *g)
{
	if (!g)
		return ;
	g->gate_count = gate_count_map(g);
	if (g->gate_count <= 0)
		return ;
	g->gates = (t_pacdot *)malloc(sizeof(t_pacdot) * g->gate_count);
	if (!g->gates)
		exit_game(EXIT_MALLOC, g);
	gate_fill_from_map(g);
}
