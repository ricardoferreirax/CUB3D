/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:11:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 22:03:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	set_player_orientation_ns(t_game *g, char c)
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

static void	set_player_orientation_ew(t_game *g, char c)
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

static void	set_player_spawn(t_game *game, int col, int row, char dir)
{
	if (game->map.grid[row][col] == VOID)
		exit_game(EXIT_MAP, game,
			"set_player_spawn() found player in VOID tile");
	if (map_get_tile(game, row, col + 1) == VOID
		|| map_get_tile(game, row, col - 1) == VOID
		|| map_get_tile(game, row + 1, col) == VOID
		|| map_get_tile(game, row - 1, col) == VOID)
		exit_game(EXIT_MAP, game,
			"set_player_spawn() player next to VOID tile");
	game->player.pos_x = (double)col + 0.5;
	game->player.pos_y = (double)row + 0.5;
	set_player_orientation_ns(game, dir);
	set_player_orientation_ew(game, dir);
	// game->map.grid[row][col] = OPEN_SPACE;
}

static t_point	find_player_spawn(t_game *game)
{
	int		y;
	int		x;
	bool	spawn_count;
	char	tile;
	t_point spawn;

	spawn_count = false;
	y = -1;
	while (++y < game->map.height)
	{  
		x = -1;
		while (++x < game->map.width)
		{
			tile = game->map.grid[y][x];
			if (tile == 'N' || tile == 'S'
				|| tile == 'E' || tile == 'W')
			{
				if(spawn_count)
					exit_game(EXIT_MAP, game, "find_player_spawn() has found more than one player");
				spawn_count = true;
				spawn.x = x;
				spawn.y = y;
				// set_player_spawn(game, x, y, tile);
			}  
		} 
	}
	if(!spawn_count)
		exit_game(EXIT_MAP, game, "find_player_spawn() has not found a player");

	return (spawn);
}  
 
void	init_player(t_game *game)
{
	t_point	spawn_count;

	if (!game || !game->map.grid)
		exit_game(EXIT_MAP, game,
			"init_player() invalid map pointers");
	spawn_count = find_player_spawn(game);
	set_player_spawn(game, spawn_count.x, spawn_count.y, game->map.grid[spawn_count.y][spawn_count.x]);
}
