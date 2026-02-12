/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:15:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 22:27:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	wall_texture_adjust_x(t_game *g, t_image *tex, int tex_x)
{
	if (g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		return (tex->width - tex_x - 1);
	if (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0)
		return (tex->width - tex_x - 1);
	return (tex_x);
}

static int	wall_texture_calc_x(t_game *g, t_image *tex)
{
	double	wall_x;
	int		tex_x;

	if (g->ray.hit_side == 0)
		wall_x = g->player.pos_y + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else
		wall_x = g->player.pos_x + g->ray.perp_wall_dist * g->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (wall_texture_adjust_x(g, tex, tex_x));
}

static void	draw_textured_column(t_game *g, int screen_x, t_image *tex, int tex_x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;

	if (g->ray.line_h <= 0)
		return ;
	step = (double)tex->height / (double)g->ray.line_h;
	tex_pos = (g->ray.draw_start - (g->win.height / 2.0) + (g->ray.line_h / 2.0)) * step;
	y = g->ray.draw_start;
	while (y <= g->ray.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel_fast(&g->win.frame_buffer, screen_x, y, (int)tex_pixel(tex, tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}

void	render_wall_column_textured(t_game *g, int screen_x)
{
	t_image	*tex;
	int		tex_x;

	tex = texture_pick_wall(g);
	tex_x = wall_texture_calc_x(g, tex);
	draw_textured_column(g, screen_x, tex, tex_x);
}
