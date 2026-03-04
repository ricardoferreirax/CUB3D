/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:42:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/04 09:58:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

int	player_hits_wall(t_game *g, int row, int col)
{
	char	tile;

	tile = map_get_tile(g, row, col);
	if (tile == WALL || tile == 'M' || tile == VOID)
		return (1);
	if (tile == GATE && g->gate_passable == 0)
		return (1);
	return (0);
}

int	ghost_hits_wall(t_game *g, int row, int col)
{
	char	tile;

	tile = map_get_tile(g, row, col);
	if (tile == WALL || tile == 'M' || tile == VOID)
		return (1);
	if (tile == GATE && g->gate_passable == 0)
		return (1);
	return (0);
}

static void	player_collision(t_game *g)
{
	t_player	*player;
	int			tile_right;
	int			tile_left;
	int			tile_bottom;
	int			tile_top;

	player = &g->player;
	tile_right = (int)(player->pos_x + PLAYER_RADIUS);
	tile_left = (int)(player->pos_x - PLAYER_RADIUS);
	tile_bottom = (int)(player->pos_y + PLAYER_RADIUS);
	tile_top = (int)(player->pos_y - PLAYER_RADIUS);
	if (player_hits_wall(g, (int)player->pos_y, tile_left))
		player->pos_x = (tile_left + 1) + PLAYER_RADIUS;
	if (player_hits_wall(g, (int)player->pos_y, tile_right))
		player->pos_x = tile_right - PLAYER_RADIUS;
	if (player_hits_wall(g, tile_top, (int)player->pos_x))
		player->pos_y = (tile_top + 1) + PLAYER_RADIUS;
	if (player_hits_wall(g, tile_bottom, (int)player->pos_x))
		player->pos_y = tile_bottom - PLAYER_RADIUS;
}

void	update_player_movement(t_game *g, double dx, double dy)
{
	g->player.pos_x += dx;
	g->player.pos_y += dy;
	player_wrap_position(g);
	player_collision(g);
	player_collect_pacdots(g);
}
