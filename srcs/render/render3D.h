/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:43:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 23:52:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER3D_H
# define RENDER3D_H

typedef struct s_image	t_image;
typedef struct s_game	t_game;

typedef struct s_fc
{
	double	fx;
	double	fy;
	double	stepx;
	double	stepy;
	double	rowdist;
}	t_fc;

typedef struct s_raycasting
{
	double	*z_buffer;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit_side;
	double	perp_wall_dist;

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
void	render_wall_column_textured(t_game *g, int screen_x);
void	render_floor(t_game *g);
void	render_ceiling(t_game *g);
