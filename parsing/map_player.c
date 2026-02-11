/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:11:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 17:28:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	set_dir_plane_from_char(t_game *g, char c)
{
	if (c == 'N')
	{
		g->player.dir_x = 0;  g->player.dir_y = -1;
		g->player.plane_x = 0.66; g->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		g->player.dir_x = 0;  g->player.dir_y = 1;
		g->player.plane_x = -0.66; g->player.plane_y = 0;
	}
	else if (c == 'E')
	{
		g->player.dir_x = 1;  g->player.dir_y = 0;
		g->player.plane_x = 0; g->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		g->player.dir_x = -1; g->player.dir_y = 0;
		g->player.plane_x = 0; g->player.plane_y = -0.66;
	}
	else
	{
		g->player.dir_x = 1;  g->player.dir_y = 0;
		g->player.plane_x = 0; g->player.plane_y = 0.66;
	}
}

static int	is_spawn_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	apply_player_spawn(t_game *g, int x, int y, char dir)
{
	g->player.pos_x = (double)x + 0.5;
	g->player.pos_y = (double)y + 0.5;
	set_dir_plane_from_char(g, dir);
	g->map.grid[y][x] = OPEN_SPACE;
}

void	init_player_from_map(t_game *g)
{
	int		y;
	int		x;
	int		count;
	char	t;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			t = g->map.grid[y][x];
			if (is_spawn_dir(t))
			{
				count++;
				apply_player_spawn(g, x, y, t);
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		exit_game(EXIT_MAP, g);
}
