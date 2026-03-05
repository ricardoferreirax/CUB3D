/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:42:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 17:58:29 by rmedeiro         ###   ########.fr       */
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
	int			col;
	int			row;

	player = &g->player;
	row = (int)player->pos_y; // converte a posiçao do player para as coordenadas do tile
	col = (int)(player->pos_x - PLAYER_RADIUS); // converte a posiçao do player para as coordenadas do tile considerando o raio do player para detectar colisões com as paredes
	if (player_hits_wall(g, row, col)) // se o player colidir com uma parede
		player->pos_x = col + 1 + PLAYER_RADIUS; // ajusta a posição do player para ficar encostado a parede considerando o raio do player
	col = (int)(player->pos_x + PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos_x = col - PLAYER_RADIUS;
	col = (int)player->pos_x;
	row = (int)(player->pos_y - PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos_y = row + 1 + PLAYER_RADIUS;
	row = (int)(player->pos_y + PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos_y = row - PLAYER_RADIUS;
}

void	apply_player_movement(t_game *g, double dx, double dy)
{
	g->player.pos_x += dx;
	g->player.pos_y += dy;
	player_wrap_position(g);
	player_collision(g);
	player_collect_pacdots(g);
}
