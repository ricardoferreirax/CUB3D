/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:42:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 18:14:47 by rmedeiro         ###   ########.fr       */
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

void	player_collision(t_game *g)
{
	t_player	*player;
	int			col;
	int			row;

	player = &g->player;
	row = (int)player->pos.tile_pos.y;                   
		// converte a posiçao do player para as coordenadas do tile
	col = (int)(player->pos.tile_pos.x - PLAYER_RADIUS); 
		// converte a posiçao do player para as coordenadas do tile considerando o raio do player para detectar colisões com as paredes
	if (player_hits_wall(g, row, col))                   
		// se o player colidir com uma parede
		player->pos.tile_pos.x = col + 1 + PLAYER_RADIUS;
			// ajusta a posição do player para ficar encostado a parede considerando o raio do player
	col = (int)(player->pos.tile_pos.x + PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.x = col - PLAYER_RADIUS;
	col = (int)player->pos.tile_pos.x;
	row = (int)(player->pos.tile_pos.y - PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.y = row + 1 + PLAYER_RADIUS;
	row = (int)(player->pos.tile_pos.y + PLAYER_RADIUS);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.y = row - PLAYER_RADIUS;
}
