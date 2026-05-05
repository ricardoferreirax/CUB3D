/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:44:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 18:52:36 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_DEBUG_H
# define RAY_DEBUG_H

# include "../Pac_Struct.h"
# include "../render/render3D.h"

# define DEBUG_CELL 12
# define DEBUG_OFF_X 20
# define DEBUG_OFF_Y 20
# define DEBUG_RAY_STEP 20

# define DEBUG_COLOR_BG 0x000000
# define DEBUG_COLOR_WALL 0xFFFFFF
# define DEBUG_COLOR_GRID 0x444444
# define DEBUG_COLOR_RAY 0x00FF00
# define DEBUG_COLOR_PLAYER 0xFFFF00
# define DEBUG_COLOR_HIT 0xFF0000

int		debug_abs(int n);
t_point	debug_point(int x, int y);
t_point	debug_world_to_screen(double x, double y);
void	debug_put_pixel(t_game *g, t_point p, int color);
int		debug_get_tile_color(t_game *g, int x, int y);

void	debug_fill_cell(t_game *g, t_point p, int color);
void	debug_draw_hit_marker(t_game *g, t_point p);
void	debug_draw_player_marker(t_game *g, t_point p);
void	debug_draw_tile(t_game *g, int x, int y);
void	debug_draw_map(t_game *g);

t_point	debug_get_line_delta(t_point a, t_point b);
t_point	debug_get_line_step(t_point a, t_point b);
void	debug_advance_line(t_point *p, t_point d, t_point s, int *err);
void	debug_draw_ray_line(t_game *g, t_point a, t_point b);

int		debug_cast_screen_ray(t_game *g, int col, t_raycasting *ray);
t_point	debug_get_ray_hit_point(t_game *g, t_raycasting ray);
void	debug_draw_casted_ray(t_game *g, t_point start, t_raycasting ray);

void	render_raycast_debug(t_game *g);

#endif
