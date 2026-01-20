/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/20 16:44:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

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
				g->player.pos_x = x + 0.5;
				g->player.pos_y = y + 0.5;
				g->player.dir_x = 1.0;
				g->player.dir_y = 0.0;
				g->player.plane_x = 0.0;
				g->player.plane_y = 0.66;
				g->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	exit_game(EXIT_MAP, g);
}
