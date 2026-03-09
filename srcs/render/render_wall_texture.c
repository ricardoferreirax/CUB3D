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
#include "render3D.h"    
#include "../textures/textures3D.h"

static int	get_wall_tex_x(t_game *g, t_image *tex)
{
	double	wall_offset;  // posição fracionária do hit na parede
	int		tex_x;  // coluna da textura que vai ser utilizada

	if (g->ray.hit_side == 0)  // se a parede atingida for vertical (lado X)
		wall_offset = g->player.pos_y + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else                                // se a parede atingida for horizontal (lado Y)
		wall_offset = g->player.pos_x + g->ray.perp_wall_dist * g->ray.ray_dir_x;
	wall_offset = fract_pos(wall_offset); // fica só com a parte decimal entre 0 e 1
	tex_x = (int)(wall_offset * (double)tex->width);    // converte esse offset para a coluna correspondente da textura
	tex_x = clamp_int(tex_x, 0, tex->width - 1);         // garante que tex_x fica dentro dos limites da textura
	if ((g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)   // se bateu no lado oeste
		|| (g->ray.hit_side == 1 && g->ray.ray_dir_y > 0)) // ou no lado sul
		tex_x = tex->width - tex_x - 1;                   // inverte a textura horizontalmente
	return (tex_x);                    // devolve a coluna da textura a usar
}

void	render_wall_column(t_game *g, int screen_x)
{
	t_image	*wall_tex;     // textura da parede do lado atingido
	int		screen_y;      // linha atual do ecrã onde vai ser desenhado o pixel
	int		tex_x;         // coluna da textura da parede atingida
	double	tex_y_pos;     // posição vertical atual dentro da textura

	if (g->ray.line_h <= 0)    // se a altura da parede for inválida, não desenha nada
		return ;
	wall_tex = texture_pick_wall(g);   // escolhe a textura correta conforme o lado/tile atingido
	tex_x = get_wall_tex_x(g, wall_tex); // calcula a coluna horizontal da textura para esta parede
	tex_y_pos = (g->ray.draw_start - g->win.height / 2.0
			+ g->ray.line_h / 2.0)
		* ((double)wall_tex->height / g->ray.line_h); // calcula a posição inicial vertical na textura
	screen_y = g->ray.draw_start;      // começa a desenhar na primeira linha visível da parede
	while (screen_y <= g->ray.draw_end) // percorre todas as linhas da coluna da parede no ecrã
	{
		put_pixel_fast(&g->win.frame_buffer, screen_x, screen_y,
			(int)tex_pixel(wall_tex, tex_x,
			clamp_int((int)tex_y_pos, 0, wall_tex->height - 1))); // escreve no frame buffer o pixel correspondente da textura
		tex_y_pos += (double)wall_tex->height / g->ray.line_h;   // avança na textura para a próxima linha do ecrã
		screen_y++;                                              // passa para a próxima linha do ecrã
	}
}
