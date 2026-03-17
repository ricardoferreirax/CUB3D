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
		g->player.dir.x = 0;
		g->player.dir.y = -1;
		g->player.plane.x = 0.66;
		g->player.plane.y = 0;
	}
	else if (c == 'S')
	{
		g->player.dir.x = 0;
		g->player.dir.y = 1;
		g->player.plane.x = -0.66;
		g->player.plane.y = 0;
	}
}

static void	set_player_orientation_ew(t_game *g, char c)
{
	if (c == 'E')
	{
		g->player.dir.x = 1;
		g->player.dir.y = 0;
		g->player.plane.x = 0;
		g->player.plane.y = 0.66;
	}
	else if (c == 'W')
	{
		g->player.dir.x = -1;
		g->player.dir.y = 0;
		g->player.plane.x = 0;
		g->player.plane.y = -0.66;
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
	game->player.pos.tile_pos.x = (double)col + 0.5;
	game->player.pos.tile_pos.y = (double)row + 0.5;
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

void player_sprites(t_game *game)
{
	int death_frames[12] = {226, 227, 228, 229, 230 , 231, 236, 237, 238, 239, 240, 241};
	game->player.frames.up[0] = game->sprite_sheet.sprites[213];
	game->player.frames.up[1] = game->sprite_sheet.sprites[212];
	game->player.frames.up[2] = game->sprite_sheet.sprites[252];
	game->player.frames.right[0] = game->sprite_sheet.sprites[242];
	game->player.frames.right[1] = game->sprite_sheet.sprites[232];
	game->player.frames.right[2] = game->sprite_sheet.sprites[252];
	game->player.frames.down[0] = game->sprite_sheet.sprites[243];
	game->player.frames.down[1] = game->sprite_sheet.sprites[233];
	game->player.frames.down[2] = game->sprite_sheet.sprites[252];
	game->player.frames.left[0] = game->sprite_sheet.sprites[211];
	game->player.frames.left[1] = game->sprite_sheet.sprites[210];
	game->player.frames.left[2] = game->sprite_sheet.sprites[252];
	int i = 0;
	while(i < 12)
	{
		ft_printf("Searchin Frame Number: %d with index %d\n", death_frames[i], i);
		game->player.frames.death[i] = game->sprite_sheet.sprites[death_frames[i]];
		i++;
	}
}
 
void	init_player(t_game *game)
{
	t_point	spawn_coord;

	if (!game || !game->map.grid)
		exit_game(EXIT_MAP, game,
			"init_player() invalid map pointers");
	spawn_coord = find_player_spawn(game);
	set_player_spawn(game, spawn_coord.x, spawn_coord.y, game->map.grid[spawn_coord.y][spawn_coord.x]);
	// set_player_spawn(game, spawn_coord.y, spawn_coord.x, game->map.grid[spawn_coord.y][spawn_coord.x]);
	player_sprites(game);










}
