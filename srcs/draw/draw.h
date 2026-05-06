/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:22:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 15:33:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../Pac_Struct.h"
# include "../render/render3D.h"

void	draw_floor_color(t_image *img, int color, int horizon);
void	draw_ceiling_color(t_image *img, int color, int horizon);
void	draw_menu(t_game *g);
int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp);
int	build_sprite_box(t_game *g, t_sprite *sp, int scale_div);
void	draw_sprite(t_game *g, t_sprite *sp, t_image *tex);
int	draw_sprite_column(t_game *g, t_sprite *sp, int col, t_image *tex);
void	draw_wall_column(t_game *g, int screen_x);

#endif
