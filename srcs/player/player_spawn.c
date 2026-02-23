/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:11:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/23 23:41:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	set_dir_plane_ns(t_game *g, char c)
{
	if (c == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1;
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
}

static void	set_dir_plane_ew(t_game *g, char c)
{
	if (c == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
	}
}

static void	apply_player_spawn(t_game *g, int x, int y, char dir)
{
	if (g->map.grid[y][x] == VOID)
		exit_game(EXIT_MAP, g);
	if (map_get_tile(g, y, x + 1) == VOID
		|| map_get_tile(g, y, x - 1) == VOID
		|| map_get_tile(g, y + 1, x) == VOID
		|| map_get_tile(g, y - 1, x) == VOID)
		exit_game(EXIT_MAP, g);
	g->player.pos_x = (double)x + 0.5;
	g->player.pos_y = (double)y + 0.5;
	set_dir_plane_ns(g, dir);
	set_dir_plane_ew(g, dir);
	g->map.grid[y][x] = OPEN_SPACE;
}

static int	map_find_player_spawn(t_game *g)
{
	int		y;
	int		x;
	int		count;
	char	t;

	count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			t = g->map.grid[y][x];
			if (t == 'N' || t == 'S' || t == 'E' || t == 'W')
			{
				count++;
				apply_player_spawn(g, x, y, t);
			}
			x++;
		}
		y++;
	}
	return (count);
}

void	init_player_from_map(t_game *g)
{
	int	count;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g);
	count = map_find_player_spawn(g);
	if (count != 1)
		exit_game(EXIT_MAP, g);
}
