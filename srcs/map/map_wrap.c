/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/03 21:59:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	map_is_wrap_tile(t_game *g, int row, int col)
{
	int	last;

	last = map_wrap_last_col(g, row);
	if (last < 1)
		return (0);
	if (map_get_tile(g, row, 0) != WRAP_PORTS)
		return (0);
	if (map_get_tile(g, row, last) != WRAP_PORTS)
		return (0);
	if (col != 0 && col != last)
		return (0);
	if (map_tile_type(map_get_tile(g, row - 1, col), TILE_VOID)
		|| map_tile_type(map_get_tile(g, row + 1, col), TILE_VOID))
		return (0);
	if (col == 0 && !map_tile_type(map_get_tile(g, row, 1), TILE_WALKABLE))
		return (0);
	if (col == last && !map_tile_type(map_get_tile(g, row, last - 1), TILE_WALKABLE))
		return (0);
	return (1);
}

int	map_wrap_last_col(t_game *g, int row)
{
	int	last;

	if (!g || !g->map.grid || row < 0 || row >= g->map.height)
		return (-1);
	last = (int)ft_strlen(g->map.grid[row]) - 1;
	while (last >= 0
		&& (g->map.grid[row][last] == '\n' || g->map.grid[row][last] == '\r'))
		last--;
	if (last < 1)
		return (-1);
	if (g->map.grid[row][0] != WRAP_PORTS || g->map.grid[row][last] != WRAP_PORTS)
		return (-1);
	return (last);
}

double	get_sprite_wrap_offset_x(t_game *g, double sprite_x, double sprite_y)
{
	double	offset_x;
	double	map_width;
	int		player_row;
	int		sprite_row;
	int		last;

	if (!g)
		return (0.0);
	offset_x = sprite_x - g->player.pos_x;
	player_row = (int)g->player.pos_y;
	sprite_row = (int)sprite_y;
	if (sprite_row != player_row)
		return (offset_x);
	last = map_wrap_last_col(g, player_row);
	if (last < 0)
		return (offset_x);
	map_width = (double)(last + 1);
	if (offset_x > map_width / 2.0)
		offset_x -= map_width;
	else if (offset_x < -map_width / 2.0)
		offset_x += map_width;
	return (offset_x);
}

int	ray_apply_wrap_x(t_game *g)
{
	int	last;

	if (!g)
		return (0);
	last = map_wrap_last_col(g, g->ray.map_y);
	if (last < 0)
		return (0);
	if (g->ray.map_x < 0)
		g->ray.map_x = last;
	else if (g->ray.map_x > last)
		g->ray.map_x = 0;
	return (1);
}

void	player_wrap_position(t_game *g)
{
	int		row;
	int		last;
	double	width;

	if (!g)
		return ;
	row = (int)g->player.pos_y;
	last = map_wrap_last_col(g, row);
	if (last < 0)
		return ;
	width = (double)(last + 1);
	while (g->player.pos_x < 0.0)
		g->player.pos_x += width;
	while (g->player.pos_x >= width)
		g->player.pos_x -= width;
}
