/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:15:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/07 23:09:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"
#include "../textures/textures3D.h"

static int	get_wall_tex_x(t_game *g, t_image *tex)
{
	double	wall_hit_pos;
	int		tex_x;

	if (g->ray.hit_side == 0)
		wall_hit_pos = g->player.pos_y + g->ray.perp_wall_dist 
			* g->ray.ray_dir_y;
	else
		wall_hit_pos = g->player.pos_x + g->ray.perp_wall_dist 
			* g->ray.ray_dir_x;
	wall_hit_pos = fract_pos(wall_hit_pos);
	tex_x = (int)(wall_hit_pos * tex->width);
	tex_x = clamp_int(tex_x, 0, tex->width - 1);
	if ((g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		|| (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_tex_col(t_game *g, int screen_x, t_image *tex, int tex_x)
{
	int		row;
	int		tex_y;
	double	tex_step;
	double	tex_pos;

	if (g->ray.line_h <= 0)
		return ;
	tex_step = (double)tex->height / g->ray.line_h;
	tex_pos = (g->ray.draw_start - g->win.height / 2.0
			+ g->ray.line_h / 2.0) * tex_step;
	row = g->ray.draw_start;
	while (row <= g->ray.draw_end)
	{
		tex_y = clamp_int((int)tex_pos, 0, tex->height - 1);
		put_pixel_fast(&g->win.frame_buffer, screen_x, row,
			(int)tex_pixel(tex, tex_x, tex_y));
		tex_pos += tex_step;
		row++;
	}
}

void	render_wall_column(t_game *g, int screen_x)
{
	t_image	*tex;

	tex = texture_pick_wall(g);
	draw_wall_tex_col(g, screen_x, tex, get_wall_tex_x(g, tex));
}
