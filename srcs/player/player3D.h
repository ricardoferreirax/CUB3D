/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 14:11:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER3D_H
# define PLAYER3D_H

#define PLAYER_SPEED    0.08
#define ROT_SPEED    0.06
#define PLAYER_RADIUS   0.18

typedef struct s_game	t_game;

void	player_movement_controller(t_game *g);
void	player_rotation_controller(t_game *g);
void	move_radius_check(t_game *g, double x_delta, double y_delta);
void		player_eat_pacdots(t_game *g);
int	is_wall_ghost(t_game *g, int y, int x);
int	is_wall_player(t_game *g, int y, int x);
void	init_player_from_map(t_game *g);
void	handle_gate_input(t_game *g);

#endif
