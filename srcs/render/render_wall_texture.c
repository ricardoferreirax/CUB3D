/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:15:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/09 13:27:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../textures/textures3D.h"
#include "render3D.h"

static int	get_wall_tex_x(t_game *g, t_image *tex)
{
	double wall_offset; // posição fracionária do hit na parede
	int tex_x;          // coluna da textura que vai ser utilizada
	if (g->ray.hit_side == 0) // se a parede atingida for vertical (lado X)
		wall_offset = g->player.pos.tile_pos.y + g->ray.perp_wall_dist
			* g->ray.ray_dir_y;
	else // se a parede atingida for horizontal (lado Y)
		wall_offset = g->player.pos.tile_pos.x + g->ray.perp_wall_dist
			* g->ray.ray_dir_x;
	wall_offset = fract_pos(wall_offset);                 
		// fica só com a parte decimal entre 0 e 1
	tex_x = (int)(wall_offset * (double)tex->width);      
		// converte esse offset para a coluna correspondente da textura
	tex_x = clamp_int(tex_x, 0, tex->width - 1);          
		// garante que tex_x fica dentro dos limites da textura
	if ((g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)    
		// se bateu no lado oeste
		|| (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0)) // ou no lado sul
		tex_x = tex->width - tex_x - 1;                   
			// inverte a textura horizontalmente
	return (tex_x);                                       
		// devolve a coluna da textura a usar
}

void	render_wall_column(t_game *g, int screen_x)
{
	t_image			*wall_tex;
	int				screen_y;
	int				tex_x;
	double			tex_y_pos;
	int				tex_y;
	double			step;
	unsigned int	*data;
	int				stride;

	if (g->ray.line_h <= 0)
		return ;
	wall_tex = texture_pick_wall(g);
	tex_x = get_wall_tex_x(g, wall_tex);
	tex_y_pos = (g->ray.draw_start - g->win.height / 2.0 + g->ray.line_h / 2.0)
		* ((double)wall_tex->height / g->ray.line_h);
	screen_y = g->ray.draw_start;
	step = (double)wall_tex->height / g->ray.line_h;
	if (!wall_tex->img_addr)
	{
		while (screen_y <= g->ray.draw_end)
		{
			put_pixel_fast(&g->win.frame_buffer, screen_x, screen_y, 128);
			screen_y++;
		}
		return ;
	}
	data = (unsigned int *)wall_tex->img_addr;
	stride = wall_tex->l_len >> 2;
	while (screen_y <= g->ray.draw_end)
	{
		tex_y = (int)tex_y_pos;
		// clamp (can also be optimized later)
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= wall_tex->height)
			tex_y = wall_tex->height - 1;
		put_pixel_fast(&g->win.frame_buffer, screen_x, screen_y, data[tex_y
			* stride + tex_x]);
		tex_y_pos += step;
		screen_y++;
	}
}
