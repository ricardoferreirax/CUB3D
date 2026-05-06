/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:15:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/06 17:34:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../textures/textures3D.h"
#include "draw.h"

static int	get_wall_tex_x(t_game *g, t_image *tex)
{
	double	wall_x;
	int		tex_x;

	if (g->ray.hit_side == 0)
		wall_x = g->player.pos.tile_pos.y + g->ray.perp_wall_dist 
			* g->ray.ray_dir_y;
	else
		wall_x = g->player.pos.tile_pos.x + g->ray.perp_wall_dist 
			* g->ray.ray_dir_x;
	wall_x = fract_pos(wall_x);
	tex_x = (int)(wall_x * tex->width);
	tex_x = clamp_int(tex_x, 0, tex->width - 1);
	if ((g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		|| (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_texture(t_game *g, t_image *tex, int x, int tex_x)
{
	unsigned int	*data;
	double			tex_pos;
	double			step;
	int				y;
	int				tex_y;

	data = (unsigned int *)tex->img_addr;
	step = (double)tex->height / g->ray.line_h;
	tex_pos = (g->ray.draw_start - g->win.height / 2.0
			+ g->ray.line_h / 2.0) * step;
	y = g->ray.draw_start;
	while (y <= g->ray.draw_end)
	{
		tex_y = clamp_int((int)tex_pos, 0, tex->height - 1);
		put_pixel_fast(&g->win.frame_buffer, x, y,
			data[tex_y * (tex->l_len >> 2) + tex_x]);
		tex_pos += step;
		y++;
	}
}

void	draw_wall_column(t_game *g, int x)
{
	t_image	*tex;
	int		y;

	if (!g || g->ray.line_h <= 0)
		return ;
	tex = texture_pick_wall(g);
	if (!tex)
		return ;
	if (!tex->img_addr || tex->width <= 0 || tex->height <= 0)
	{
		y = g->ray.draw_start;
		while (y <= g->ray.draw_end)
			put_pixel_fast(&g->win.frame_buffer, x, y++, 128);
		return ;
	}
	draw_wall_texture(g, tex, x, get_wall_tex_x(g, tex));
}
