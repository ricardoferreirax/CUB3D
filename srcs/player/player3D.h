/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 21:39:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#ifndef PLAYER3D_H
# define PLAYER3D_H

#define PLAYER_SPEED    0.08
#define ROT_SPEED    0.06
#define PLAYER_RADIUS   0.18

typedef struct s_game	t_game;

void	player_controller(t_game *g);
void	player_collision(t_game *g);
bool		player_collect_pacdots(t_game *g);
int	player_hits_wall(t_game *g, int row, int col);
int	ghost_hits_wall(t_game *g, int row, int col);
void	init_player(t_game *g);

#endif
