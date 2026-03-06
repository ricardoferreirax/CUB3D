/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:51:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 21:18:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"
//
// int	ft_abs(int n)
// {
// 	if (n < 0)
// 		return (-n);
// 	return (n);
// }
//
// // direction vectors
// // left 01,00
// // right -01,00
// // down 00,01
// // up 00,-01
//
// // this only is useful to compare distance is it doesn't sqrt(9 the result)
// int	distance_to_target(t_ghost *ghost, int dy, int dx)
// {
// 	int	result;
//
// 	result = pow(((ghost->pos.tile_pos.x + dx) - ghost->target_tile.x), 2)
// 		+ pow(((ghost->pos.tile_pos.y + dy) - ghost->target_tile.y), 2);
// 	return (result);
// }
//
// t_point	chose_next_move(t_ghost *ghost, char **map)
// {
// 	int		i;
// 	int		best;
// 	int		best_dir;
// 	int		dist;
// 	t_point	dir;
//
// 	int direction[4][2] = 
// 	{
// 		{-1, 0}, // 0 = up
// 		{0, -1}, // 1 = left
// 		{1, 0},  // 2 = down
// 		{0, 1}   // 3 = right
// 	};
// 	i = 0;
// 	best = -1;
// 	best_dir = -1;
// 	// print_2d(map);
// 	while (i < 4)
// 	{
// 		if (map[(int)ghost->pos.tile_pos.y + direction[i][0]][(int)ghost->pos.tile_pos.x + direction[i][1]] != '1' && i != ghost->invalid_dir)
// 		{
// 			dist = distance_to_target(ghost, direction[i][0], direction[i][1]);
// 			if (best == -1 || dist < best)
// 			{
// 				best = dist;
// 				best_dir = i;
// 			}
// 		}
// 		i++;
// 	}
// 	if (best_dir == -1)
// 		best_dir = (ghost->invalid_dir + 2) % 4;
// 	ghost->invalid_dir = (best_dir + 2) % 4;
// 	dir.y = direction[best_dir][0];
// 	dir.x = direction[best_dir][1];
// 	return (dir);
// }
//
// void move(char** map, t_ghost *ghost, int dx, int dy)
// {
// 	char ghost_to_move = which_ghost(ghost);
//
// 	int new_posx = ghost->pos.tile_pos.x + dx;
// 	int new_posy = ghost->pos.tile_pos.y + dy;
// 	map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = '0';
// 	if(ghost->is_steping_on_pacdot)
// 	{ 
// 		if(ghost->is_steping_on_pacdot > 0)
// 			map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = 'D';
// 		if (ghost->is_steping_on_pacdot > 1)
// 			map[ghost->pos.tile_pos.y][ghost->pos.tile_pos.x] = 'E';
// 		ghost->is_steping_on_pacdot = 0;
// 	}
// 	if(map[new_posy][new_posx] != '0')
// 	{
// 		if(map[new_posy][new_posx] == 'D')
// 			ghost->is_steping_on_pacdot = 1;
// 		else if(map[new_posy][new_posx] == 'E')
// 			ghost->is_steping_on_pacdot = 2;
// 	}
// 	map[new_posy][new_posx] = ghost_to_move;
// }
//
//
// void	update_ghosts(t_game *g, double dt)
// {
// 	int	i;
//
// 	if (!g)
// 		return ;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		update_ghost(g, &g->ghosts[i], dt);
// 		i++;
// 	}
// }
