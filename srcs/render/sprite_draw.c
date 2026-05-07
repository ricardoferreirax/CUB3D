/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/12 12:19:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp)
{
	double	cam_inv_det;
	double	depth;

	double dx; // deslocamento do sprite no eixo x em relação ao player
	double dy; // deslocamento do sprite no eixo y em relação ao player
	// inverso do determinante da matriz para converter as coordenadas do mundo para coordenadas da tela
	// distancia do sprite à camera do player (distancia perpendicular ao plano da camera)
	if (!g || !sp)
		return (0);
	dx = get_sprite_wrap_offset_x(g, wx, wy);
	// calcula o deslocamento do sprite no eixo x considerando o wrap do mapa
	dy = wy - g->player.pos.tile_pos.y;
	// calcula o deslocamento do sprite no eixo y em relação ao player
	cam_inv_det = 1.0 / (g->player.plane.x * g->player.dir.y - g->player.dir.x
			* g->player.plane.y);
	depth = cam_inv_det * (-g->player.plane.y * dx + g->player.plane.x * dy);
	// calcula a distancia perpendicular do sprite à camera do player
	if (depth <= 0.01)
		// se o sprite estiver muito perto ou atrás do player, não projeta
		return (0);
	sp->dist = depth;
	// guarda a distancia do sprite
	sp->screen_x = (int)(g->win.width * 0.5 * (1.0 + (cam_inv_det
					* (g->player.dir.y * dx - g->player.dir.x * dy)) / depth));
	// calcula a posição horizontal do sprite na tela (coluna onde o centro do sprite deve ser desenhado)
	return (1);
	// projeção bem sucedida
}

int	sprite_build(t_game *g, t_sprite *sp, int scale_div)
{
	int	offset_y;

	int size;     // tamanho do sprite projetado na tela
	int center_y; // centro vertical da tela para o sprite
	size = (int)((double)g->win.height / sp->dist);
	if (size < 0)
		size = -size;
	size /= scale_div;
	if (size < 2)
		return (0);
	center_y = g->win.height / 2;
	offset_y = (int)(0.10 * g->win.height / sp->dist);
	sp->size = size;
	sp->tex_start_x = sp->screen_x - size / 2;
	sp->tex_start_y = center_y - size / 2 + offset_y;
	sp->draw_start_x = clamp_int(sp->tex_start_x, 0, g->win.width - 1);
	sp->draw_end_x = clamp_int(sp->tex_start_x + size, 0, g->win.width - 1); 
	sp->draw_start_y = clamp_int(sp->tex_start_y, 0, g->win.height - 1);     
	sp->draw_end_y = clamp_int(sp->tex_start_y + size, 0, g->win.height - 1);
	return (sp->draw_start_x < sp->draw_end_x
		&& sp->draw_start_y < sp->draw_end_y);
}

void	sprite_draw(t_game *g, t_sprite *sp, t_image *tex)
{
	double	*zbuf;

	int col; // coluna atual da tela onde o sprite está a ser desenhado
	if (!g || !sp || !tex || !tex->img_addr)
		return ;
	if (!g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	zbuf = g->ray.z_buffer;
	col = sp->draw_start_x;
	while (col < sp->draw_end_x) // percorre todas as colunas do sprite
	{
		if (sp->dist < zbuf[col])
			sprite_draw_col(g, sp, col, tex); // desenha a coluna do sprite
		col++;
	}
}
