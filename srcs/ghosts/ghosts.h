/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:21:48 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 11:17:53 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTS_H
# define GHOSTS_H

# include "../../Pac_Struct.h"

t_double_point	continue_travel(t_game *game, t_ghost *ghost, int ignore_walls);

void			ghost_move_pixel(t_ghost *gh, int dx, int dy);
bool			cannot_move_up(t_game *game, t_ghost *ghost);
int				chose_next_move(t_game *game, t_ghost *ghost, t_map *map);
void			ghost_set_pixel_pos(t_ghost *gh, double px, double py);
int				update_ghost(t_game *game, t_ghost *ghost);
bool			is_on_penhouse(t_point ghost_pos, t_point gate_pos);
int				ghost_penhouse_dance(t_game *game, t_ghost *ghost,
					t_point gate);
bool			can_ghost_exit_penhouse(t_game *game, t_ghost *ghost);
int				ghost_in_penhouse(t_ghost *ghost, char **map);
void			update_target(t_game *game, t_ghost *ghost);
t_point			chase_player(t_game *game, t_ghost *ghost);
t_point			ghost_pos_intile(t_point pos);
t_point			inky_target(t_game *game);
t_point			pinky_target(t_game *game, int n);
void			goto_penhouse(t_game *game, t_ghost *ghost);
bool			ghost_ai(t_game *game, t_ghost *ghost);
void			ghost_sprites(t_game *game, e_ghost ghost);
void			ghost_color(t_ghost *ghost);
bool			in_bounds(t_map *map, t_point coord);
bool			is_not_blocked(t_ghost *ghost, t_map *map, int direction[4][2],
					int i);
int				is_ghost_on_deadend(t_game *game, t_ghost *ghost,
					int direction[4][2], int ignore_walls);
int				passed_center(t_ghost *ghost);
int				rng_machine(void);
int				squared_distance(int x1, int y1, int x2, int y2);
#endif
