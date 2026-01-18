/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:51:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 16:35:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	init_player_from_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x] && g->map.grid[y][x] != '\n')
		{
			if (g->map.grid[y][x] == 'M')
			{
				g->view.x = x + 0.5;
				g->view.y = y + 0.5;
				g->view.dir_x = 1.0;
				g->view.dir_y = 0.0;
				g->view.plane_x = 0.0;
				g->view.plane_y = 0.66;
				g->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	exit_game(EXIT_MAP, g);
}

void	init_map_3d(t_game *g)
{
	int	y;
	int	x;
	int	max_w;

	y = 0;
	max_w = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x] && g->map.grid[y][x] != '\n')
			x++;
		if (x > max_w)
			max_w = x;
		y++;
	}
	g->map.height = y;
	g->map.width = max_w;
}
