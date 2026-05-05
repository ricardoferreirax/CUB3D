/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:05:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:46:58 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
#define BASE_H

#include "../../Pac_Struct.h" 


int	find_sprite(unsigned int mask);
int find_disamb_sprite(unsigned int mask);
t_point player_spawn(char **map);
int	which_wall(char **original_map, t_map map, t_point *coord);
int	which_tile(char **original_map, t_map *map, t_point coord, bool debug);

int squared_corners(int final);
void	put_tile_inbase(t_game *g, int tile_code, unsigned int color,
		t_point point);
#endif // !BASE_H
