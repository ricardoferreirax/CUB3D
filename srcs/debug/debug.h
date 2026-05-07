/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:44:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 18:28:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_RAYCAST_H
# define DEBUG_RAYCAST_H

# include "../Pac_Struct.h"
# include "../render/render3D.h"

# define DEBUG_CELL 12
# define DEBUG_OFF_X 20
# define DEBUG_OFF_Y 20
# define DEBUG_RAY_STEP 20

# define DEBUG_BG 0x000000
# define DEBUG_WALL 0xFFFFFF
# define DEBUG_GRID 0x444444
# define DEBUG_RAY 0x00FF00
# define DEBUG_PLAYER 0xFFFF00
# define DEBUG_HIT 0xFF0000

t_point	debug_pos(double x, double y);
void	debug_square(t_game *g, t_point p, int size, int color);
void	debug_line(t_game *g, t_point a, t_point b);
int		debug_ray(t_game *g, int col, t_raycasting *ray);
void	render_raycast_debug(t_game *g);

#endif
