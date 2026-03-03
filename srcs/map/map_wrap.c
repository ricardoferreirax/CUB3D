/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/03 21:41:34 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	map_is_wrap_tile(t_game *g, int row, int col)
{
	if (map_get_tile(g, row, 0) != WRAP_PORTS)
		return (0);
	if (map_get_tile(g, row, g->map.width - 1) != WRAP_PORTS)
		return (0);
	if (col != 0 && col != g->map.width - 1)
		return (0);
	if (map_tile_type(map_get_tile(g, row - 1, col), TILE_VOID)
		|| map_tile_type(map_get_tile(g, row + 1, col), TILE_VOID))
		return (0);
	if (col == 0 && !map_tile_type(map_get_tile(g, row, 1), TILE_WALKABLE))
		return (0);
	if (col == g->map.width - 1
		&& !map_tile_type(map_get_tile(g, row, g->map.width - 2), TILE_WALKABLE))
		return (0);
	return (1);
}

int	map_wrap_has_wrap(t_game *g, int row)
{
	if (!g || !g->map.grid)
		return (0);
	if (row < 0 || row >= g->map.height)
		return (0);
	if (g->map.width <= 1)
		return (0);
	return (g->map.grid[row][0] == WRAP_PORTS
		&& g->map.grid[row][g->map.width - 1] == WRAP_PORTS);
}

double	get_sprite_wrap_offset_x(t_game *g, double sprite_x, double sprite_y)
{
	double	offset_x;
	double	map_width;
	int		player_row;
	int		sprite_row;
	
	if (!g)
		return (0.0);
	offset_x = sprite_x - g->player.pos_x;
	player_row = (int)g->player.pos_y;
	sprite_row = (int)sprite_y;
	if (sprite_row != player_row)
		return (offset_x);
	if (!map_wrap_has_wrap(g, player_row))
		return (offset_x);
	map_width = (double)g->map.width;
	if (offset_x > map_width / 2.0)
		offset_x -= map_width;
	else if (offset_x < -map_width / 2.0)
		offset_x += map_width;
	return (offset_x);
}

int	ray_apply_wrap_x(t_game *g)
{
	int	map_width;

	if (!g)
		return (0);
	if (!map_wrap_has_wrap(g, g->ray.map_y))
		return (0);
	map_width = g->map.width;
	if (g->ray.map_x < 0)
	{
		g->ray.map_x = map_width - 1;
		return (1);
	}
	if (g->ray.map_x >= map_width)
	{
		g->ray.map_x = 0;
		return (1);
	}
	return (1);
}

void	player_wrap_position(t_game *g)
{
	int	player_row;
	int	map_width;

	if (!g)
		return ;
	player_row = (int)g->player.pos_y;
	map_width = g->map.width;
	if (!map_wrap_has_wrap(g, player_row))
		return ;
	if (g->player.pos_x < 0.0)
		g->player.pos_x += (double)map_width;
	else if (g->player.pos_x >= (double)map_width)
		g->player.pos_x -= (double)map_width;
}
