/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/09 17:40:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp)
{
	double	dx; // deslocamento do sprite no eixo x em relação ao player
	double	dy; // deslocamento do sprite no eixo y em relação ao player
	double	cam_inv_det; // inverso do determinante da matriz para converter as coordenadas do mundo para coordenadas da tela
	double	depth; // distancia do sprite à camera do player (distancia perpendicular ao plano da camera)

	if (!g || !sp)
		return (0);
	dx = get_sprite_wrap_offset_x(g, wx, wy); // calcula o deslocamento do sprite no eixo x considerando o wrap do mapa
	dy = wy - g->player.pos_y; // calcula o deslocamento do sprite no eixo y em relação ao player
	cam_inv_det = 1.0 / (g->player.plane_x * g->player.dir_y - g->player.dir_x 
		* g->player.plane_y);
	depth = cam_inv_det * (-g->player.plane_y * dx + g->player.plane_x * dy); // calcula a distancia perpendicular do sprite à camera do player 
	if (depth <= 0.01) // se o sprite estiver muito perto ou atrás do player, não projeta
		return (0);
	sp->depth = ty;
	sp->screen_x = (int)((g->win.width / 2.0) * (1.0 + tx / ty));
	return (1); }

int	sprite_build(t_game *g, t_sprite *sp, int scale_div)
{
	int	size; // tamanho do sprite projetado na tela
	int	center_y; // centro vertical da tela para o sprite
	int	offset_y; // deslocamento vertical do sprite para ajustar a posição do sprite na tela (quanto maior o offset_y, mais baixo o sprite é desenhado)

	size = (int)((double)g->win.height / sp->dist); // calcula o tamanho do sprite com base na distancia do sprite ao player (objetos mais distantes aparecem menores)
	if (size < 0)
		size = -size; // garante que o tamanho é positivo mesmo que a distancia seja negativa
	size /= scale_div; // divide o tamanho para ajustar a escala do sprite (quanto maior o scale_div, menor o sprite projetado)
	if (size < 2)
		return (0);
	center_y = g->win.height / 2;
	offset_y = (int)(0.10 * g->win.height / sp->dist);
	sp->size = size;
	sp->tex_start_x = sp->screen_x - size / 2; // posição inicial x da textura do sprite 
	sp->tex_start_y = center_y - size / 2 + offset_y; // posição inicial y da textura do sprite (ajustada para que o sprite seja desenhado um pouco mais baixo na tela)
	sp->draw_start_x = clamp_int(sp->tex_start_x, 0, g->win.width - 1); // coluna inicial onde o sprite começa a desenhar, garantindo que fica dentro dos limites da tela
	sp->draw_end_x = clamp_int(sp->tex_start_x + size, 0, g->win.width - 1); // coluna final onde o sprite termina de desenhar
	sp->draw_start_y = clamp_int(sp->tex_start_y, 0, g->win.height - 1); // linha inicial onde o sprite começa a desenhar
	sp->draw_end_y = clamp_int(sp->tex_start_y + size, 0, g->win.height - 1); // linha final onde o sprite termina de desenhar
	return (sp->draw_start_x < sp->draw_end_x
		&& sp->draw_start_y < sp->draw_end_y); // retorna 1 se o sprite tiver na area válida para desenhar na tela
}

void	sprite_draw(t_game *g, t_sprite *sp, t_image *tex)
{
	int		col; // coluna atual da tela onde o sprite está a ser desenhado
	double	*zbuf; // z-buffer do raycasting para comparar a distancia do sprite com a distancia das paredes para garantir que o sprite é desenhado na frente ou atrás das paredes corretamente

	if (!g || !sp || !tex || !tex->img_addr)
		return ;
	if (!g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	zbuf = g->ray.z_buffer;
	col = sp->draw_start_x; // começa a desenhar o sprite a partir da primeira coluna calculada na função sprite_build
	while (col < sp->draw_end_x) // percorre todas as colunas do sprite 
	{
		if (sp->dist < zbuf[col]) // verifica se o sprite está mais próximo do player do que a parede nessa coluna
			sprite_draw_col(g, sp, col, tex); // desenha a coluna do sprite 
		col++;
	}
}
