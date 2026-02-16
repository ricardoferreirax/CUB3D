/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:43:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 22:54:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER3D_H
# define RENDER3D_H

typedef struct s_game	t_game;
typedef struct s_image	t_image;
typedef struct s_ghost	t_ghost;

typedef struct s_fc
{
	double	fx;
	double	fy;
	double	stepx;
	double	stepy;
	double	rowdist;
}	t_fc;

typedef struct s_sprite
{
	double	depth;
	int		screen_x;
	int		size;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
}	t_sprite;

typedef struct s_raycasting
{
	double	*z_buffer;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		hit_side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		draw_start;
	int		draw_end;
	int		hit;
	int		line_h;
}	t_raycasting;

#endif

void	render_frame(t_game *game);
void	process_raycasting(t_game *g);
int	perform_dda(t_game *g);
void	calculate_dda_step(t_game *g);
int		register_center_hit(t_game *g, int screen_x, int hit_found);
void	put_pixel_fast(t_image *img, int x, int y, int color);
void	render_wall_col(t_game *g, int screen_x);
void	render_floor_texture(t_game *g);
void	render_ceiling_texture(t_game *g);
void	render_pacdots(t_game *g);
void	render_energizers(t_game *g);
void	render_ghosts(t_game *g);
double	fract_pos(double x);

unsigned int	tex_pixel(t_image *tex, int x, int y);
void	parse_floor_ceiling_color(t_game *g, const char *s, int *dst);
void	parse_floor_ceiling_line(t_game *g, char id, char *value);
void	fill_floor_color(t_image *img, int color, int horizon);
void	fill_ceiling_color(t_image *img, int color, int horizon);
void	convert_texture_coords(t_fc *fc, t_image *tex, int *tx, int *ty);
void	sprite_draw(t_game *g, t_sprite *b, t_image *tex);
int	sprite_project(t_game *g, double x, double y, t_sprite *b);
int	sprite_build(t_game *g, t_sprite *b, int size_div);
t_image	*ghost_tex(t_game *g, t_ghost *gh);
