/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 17:54:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	map_is_wrap_tile(t_game *g, int row, int col)
{
	int	last;

	last = map_row_last_col(g, row, 1);
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

double	get_sprite_wrap_offset_x(t_game *g, double sprite_x, double sprite_y)
{
	double	offset_x;
	double	map_width;
	int		player_row;
	int		last;

	if (!g)
		return (0.0);
	offset_x = sprite_x - g->player.pos.tile_pos.x;
	player_row = (int)g->player.pos.tile_pos.y;
	if ((int)sprite_y != player_row)
		return (offset_x);
	last = map_row_last_col(g, player_row, 1);
	if (last < 0)
		return (offset_x);
	map_width = last + 1;
	if (offset_x >= map_width / 2.0)
		offset_x -= map_width;
	else if (offset_x <= -map_width / 2.0)
		offset_x += map_width;
	return (offset_x);
}

int	ray_wrap_x(t_game *g)
{
	int	last;

	if (!g)
		return (0);
	last = map_row_last_col(g, g->ray.map_y, 1); // obtém o índice da última coluna da row onde o ray está a apontar
	if (last < 0) 
		return (0);
	if (g->ray.map_x < 0)
		g->ray.map_x = last;
	else if (g->ray.map_x > last)
		g->ray.map_x = 0;
	return (1);
}

void	ghost_wrap_position(t_game *g, t_ghost *ghost)
{
	int		row;
	int		last_col;
	double	width_px;

	if (!g || !ghost)
		return ;
	row = (int)ghost->pos.tile_pos.y;
	last_col = map_row_last_col(g, row, 1);
	if (last_col < 0)
		return ;
	width_px = (double)(last_col + 1) * 8.0;
	while (ghost->pos.pixel_pos.x < 0.0)
		ghost->pos.pixel_pos.x += width_px;
	while (ghost->pos.pixel_pos.x >= width_px)
		ghost->pos.pixel_pos.x -= width_px;
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
	while (g->player.pos.tile_pos.x < 0.0)
		g->player.pos.tile_pos.x += width;
	while (g->player.pos.tile_pos.x >= width)
		g->player.pos.tile_pos.x -= width;
	g->player.pos.pixel_pos.x = g->player.pos.tile_pos.x * TILE_SIZE;
}
