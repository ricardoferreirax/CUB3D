/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_port.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:54:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:28:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	is_valid_wrap_port(t_game *g, int y, int x)
{
	if (map_tile(g, y, 0) != WRAP_PORTS)
		return (0);
	if (map_tile(g, y, g->map.width - 1) != WRAP_PORTS)
		return (0);
	if (x != 0 && x != g->map.width - 1)
		return (0);
	if (map_tile_type(map_tile(g, y - 1, x), TILE_VOID)
		|| map_tile_type(map_tile(g, y + 1, x), TILE_VOID))
		return (0);
	if (x == 0 && !map_tile_type(map_tile(g, y, 1), TILE_WALKABLE))
		return (0);
	if (x == g->map.width - 1
		&& !map_tile_type(map_tile(g, y, g->map.width - 2), TILE_WALKABLE))
		return (0);
	return (1);
}

static int	wrap_row_is_active(t_game *g, int y)
{
	if (y < 0 || y >= g->map.height)
		return (0);
	return (map_tile(g, y, 0) == WRAP_PORTS
		&& map_tile(g, y, g->map.width - 1) == WRAP_PORTS);
}

int	try_wrap_ray_x(t_game *g)
{
	if (!wrap_row_is_active(g, g->ray.map_y))
		return (0);
	if (g->ray.map_x < 0)
	{
		g->ray.map_x = g->map.width - 2;
		return (1);
	}
	if (g->ray.map_x >= g->map.width)
	{
		g->ray.map_x = 1;
		return (1);
	}
	return (0);
}

void	wrap_port(t_game *g)
{
	int		y;
	double	offset;

	y = (int)g->player.pos_y;
	if (!wrap_row_is_active(g, y))
		return ;
	offset = PLAYER_RADIUS + 0.10;
	if (g->player.pos_x < 0.0)
		g->player.pos_x = (double)(g->map.width - 1) - offset;
	else if (g->player.pos_x > (double)(g->map.width - 1))
		g->player.pos_x = 0.0 + offset;
}
