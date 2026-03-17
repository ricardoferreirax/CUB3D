/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:15:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/16 17:48:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"
#include "../textures/textures3D.h"

static int	wall_tex_x(t_game *g, t_image *tex)
{
	double	hit;
	int		tx;

	if (g->ray.hit_side == 0)
		hit = g->player.pos.tile_pos.y + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else
		hit = g->player.pos.tile_pos.x + g->ray.perp_wall_dist * g->ray.ray_dir_x;
	hit = fract_pos(hit);
	tx = (int)(hit * (double)tex->width);
	if (tx < 0)
		tx = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	if ((g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		|| (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0))
		tx = tex->width - tx - 1;
	return (tx);
}

static void	draw_texture_col(t_game *g, int screen_x, t_image *tex, int tex_x)
{
	int		y;
	double	step;
	double	pos;
	int		tex_y;

	if (g->ray.line_h <= 0)
		return ;
	step = (double)tex->height / (double)g->ray.line_h;
	pos = (g->ray.draw_start - (g->win.height / 2.0) + (g->ray.line_h / 2.0)) * step;
	y = g->ray.draw_start;
	while (y <= g->ray.draw_end)
	{
		tex_y = (int)pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel_fast(&g->win.frame_buffer, screen_x, y, (int)tex_pixel(tex, tex_x, tex_y));
		pos += step;
		y++;
	}
}

void	render_wall_col(t_game *g, int screen_x)
{
	t_image	*tex;
	int		tex_x;

	tex = texture_pick_wall(g);
	tex_x = wall_tex_x(g, tex);
	draw_texture_col(g, screen_x, tex, tex_x);
}
