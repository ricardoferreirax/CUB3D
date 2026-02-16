/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 05:03:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER3D_H
# define PLAYER3D_H

#define PLAYER_SPEED    0.08
#define ROT_SPEED    0.06
#define PLAYER_RADIUS   0.18

typedef struct s_game	t_game;

void	movement_controller(t_game *g);
void	player_rotation_controller(t_game *g);
void	move_radius_check(t_game *g, double x_delta, double y_delta);

#endif