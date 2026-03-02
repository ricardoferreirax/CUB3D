/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:32:27 by rmedeiro         ###   ########.fr       */
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
void	update_player_movement(t_game *g, double dx, double dy);
void		player_collect_pacdots(t_game *g);
int	player_hits_wall(t_game *g, int row, int col);
int	ghost_hits_wall(t_game *g, int row, int col);
void	init_player(t_game *g);
void	handle_gate_toggle(t_game *g);

#endif
