/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:22:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 15:48:57 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../../Pac_Struct.h"
# include "../render/render3D.h"

t_image	*ghost_tex(t_game *g, t_ghost *gh);
void	draw_floor_color(t_image *img, int color, int horizon);
void	draw_ceiling_color(t_image *img, int color, int horizon);
void	draw_menu(t_game *g);
int		sprite_project(t_game *g, double wx, double wy, t_sprite *sp);
int		build_sprite_box(t_game *g, t_sprite *sp, int scale_div);
void	draw_pacdots(t_game *g);
void	draw_energizers(t_game *g);
void	draw_ghosts(t_game *g);
int		draw_sprite_column(t_game *g, t_sprite *sp, int col, t_image *tex);
void	draw_wall_column(t_game *g, int screen_x);
void	draw_plane_row(t_game *g, t_fc *plane, t_image *tex, int row);
void	set_plane(t_game *g, t_fc *plane, double dist);
void	put_pixel_fast(t_image *img, int x, int y, int color);
int	ghost_anim_frame(t_ghost *gh);
int	clamp_int(int value, int min, int max);
double	fract_pos(double x);

#endif
