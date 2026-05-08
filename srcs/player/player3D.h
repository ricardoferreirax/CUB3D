/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 16:51:34 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#ifndef PLAYER3D_H
# define PLAYER3D_H

# define PLAYER_SPEED 0.12
# define ROT_SPEED 0.06
# define PLAYER_RADIUS 0.18

typedef struct s_game	t_game;
typedef struct s_point	t_point;

void					player_controller(t_game *g);
void					player_collision(t_game *g);
bool					player_collect_pacdots(t_game *g);
int						player_hits_wall(t_game *g, int row, int col);
int						ghost_hits_wall(t_game *g, int row, int col);
void					init_player(t_game *g, int is_death);
void					player_controller(t_game *g);
void					player_collision(t_game *g);
int						player_hits_wall(t_game *g, int row, int col);
int						ghost_hits_wall(t_game *g, int row, int col);
void					player_rotate(t_game *g, double angle);
t_point	find_player_spawn(t_game *game);
bool					player_collect_energizer(t_game *g);
int	player_touched_ghost(t_game *g);
void	set_player_spawn(t_game *game, int col, int row, char dir);

#endif
