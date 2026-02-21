/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:25:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/21 21:49:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZER_H
#define INITIALIZER_H
#include "../../Pac_Struct.h"

char **copy_map(char **map);
t_point find_c(char **map,  char c);
void init_clyde(t_game *game, t_ghost *clyde);
void init_inky(t_game *game, t_ghost *inky);
void init_pinky(t_game *game, t_ghost *pinky);
void init_blinky(t_game *game, t_ghost *blinky);
#endif
