/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:05:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/12 11:21:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# include "../../Pac_Struct.h"

int				find_sprite(unsigned int mask);
int				find_disamb_sprite(unsigned int mask);
t_point			player_spawn(char **map);
int				which_wall(char **original_map, t_map map, t_point *coord);
int				which_tile(char **original_map, t_map *map, t_point coord,
					bool debug);
int				squared_corners(int final);
void			put_tile_inbase(t_game *g, int tile_code, unsigned int color,
					t_point point);
void			flood_fill(char **map, int x, int y);
int				disambiguation(t_point player_spawn, t_map map, t_point coord);
void			check_diagonal(char **map, t_point coord, unsigned char *mask,
					char c);
void			check_cardinal(char **map, t_point coord, unsigned char *mask,
					char c);

unsigned char	mask_constructor(t_map *map, t_point *coord, char c);
#endif // !BASE_H
