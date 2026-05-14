/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:14:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"

void map_validate_wrap_portals(t_game *game)
{
	t_point coord;
	coord.y = 0;
	while(coord.y < game->map.height)
	{
		coord.x = 0;
		while(coord.x < game->map.width)
		{
			if(game->map.grid[coord.y][coord.x] == 'D')
			{
				
				if(coord.x != 0 && coord.x != game->map.width - 1)
				{
					printf("%s\n", game->map.grid[coord.y]);
					while(coord.x--)
						printf(" ");
					printf("^\n");
					exit_game(EXIT_MAP, game, "Wrap Portals  must be at the start or end of the line");
				}
			}
			coord.x++;
		}
		coord.y++;
	}
}

int	map_is_wrap_tile(t_game *g, int row, int col)
{
	int	last;

	last = map_row_last_col(g, row, 1);
	if (last < 1 || col < 0)
		return (0);
	if (col != 0 && col != last)
		return (0);
	if (map_get_tile(g, row, 0) != WRAP_PORTS)
		return (0);
	if (map_get_tile(g, row, last) != WRAP_PORTS)
		return (0);
	if (map_tile_type(map_get_tile(g, row - 1, col), TILE_VOID)
		|| map_tile_type(map_get_tile(g, row + 1, col), TILE_VOID))
		return (0);
	if (col == 0)
		return (map_tile_type(map_get_tile(g, row, 1), TILE_WALKABLE));
	return (map_tile_type(map_get_tile(g, row, last - 1), TILE_WALKABLE));
}

double	get_sprite_wrap_offset_x(t_game *g, double sprite_x, double sprite_y)
{
	double	offset_x;
	double	width;
	int		row;
	int		last;

	if (!g)
		return (0.0);
	offset_x = sprite_x - g->player.pos.tile_pos.x;
	row = (int)g->player.pos.tile_pos.y;
	if ((int)sprite_y != row)
		return (offset_x);
	last = map_row_last_col(g, row, 1);
	if (last < 0)
		return (offset_x);
	width = (double)(last + 1);
	if (offset_x >= width * 0.5)
		offset_x -= width;
	else if (offset_x <= -width * 0.5)
		offset_x += width;
	return (offset_x);
}

void	ghost_wrap_position(t_game *g, t_ghost *ghost)
{
	int		row;
	int		last;
	double	width;

	if (!g || !ghost)
		return ;
	row = (int)ghost->pos.tile_pos.y;
	last = map_row_last_col(g, row, 1);
	if (last < 0)
		return ;
	width = (double)(last + 1) * TILE_SIZE;
	ghost->pos.pixel_pos.x = wrap_value(ghost->pos.pixel_pos.x, width);
	ghost->pos.tile_pos.x = ghost->pos.pixel_pos.x / TILE_SIZE;
}

void	player_wrap_position(t_game *g)
{
	int		row;
	int		last;
	double	width;

	if (!g)
		return ;
	row = (int)g->player.pos.tile_pos.y;
	last = map_row_last_col(g, row, 1);
	if (last < 0)
		return ;
	width = (double)(last + 1);
	g->player.pos.tile_pos.x = wrap_value(g->player.pos.tile_pos.x, width);
	g->player.pos.pixel_pos.x = g->player.pos.tile_pos.x * TILE_SIZE;
}
