/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:13:51 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/08 23:09:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

int	sprite_project(t_game *g, double wx, double wy, t_sprite *sp)
{
	double	dx;
	double	dy;
	double	cam_inv_det;
	double	depth;

	if (!g || !sp)
		return (0);
	dx = get_sprite_wrap_offset_x(g, wx, wy); // calcula o deslocamento horizontal do sprite ao considerar o wrap do mapa
	dy = wy - g->player.pos_y; // calcula a distância vertical do sprite em relação ao player
	cam_inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
			- g->player.dir_x * g->player.plane_y); // calcula o determinante inverso da matriz para converter as coordenadas do mapa para as coordenadas da camera
	depth = cam_inv_det * (-g->player.plane_y * dx
			+ g->player.plane_x * dy); // calcula a distância perpendicular do sprite em relação ao player, é usada para determinar o tamanho do sprite na tela
	if (depth <= 0.01)
		return (0);
	sp->depth = depth;
	sp->screen_x = (int)(g->win.width * 0.5 
		* (1.0 + (cam_inv_det * (g->player.dir_y * dx 
			- g->player.dir_x * dy)) / depth)); // calcula a coordenada horizontal do sprite na tela, centralizando-a com base na posição do player e ajustando-a de acordo com a distância do sprite
	return (1); // retorna 1 para indicar que a projeção do sprite foi bem sucedida e que o sprite deve ser desenhado
}

int	sprite_build(t_game *g, t_sprite *sp, int scale_div)
{
	int	size;
	int	center_y;
	int	offset_y;

	size = (int)((double)g->win.height / sp->depth);
	if (size < 0)
		size = -size;
	size /= scale_div;
	if (size < 2)
		return (0);
	center_y = g->win.height / 2;
	offset_y = (int)(0.10 * g->win.height / sp->depth);
	sp->size = size;
	sp->raw_x0 = sp->screen_x - size / 2;
	sp->raw_y0 = center_y - size / 2 + offset_y;
	sp->x0 = clamp_int(sp->raw_x0, 0, g->win.width - 1);
	sp->x1 = clamp_int(sp->raw_x0 + size, 0, g->win.width - 1);
	sp->y0 = clamp_int(sp->raw_y0, 0, g->win.height - 1);
	sp->y1 = clamp_int(sp->raw_y0 + size, 0, g->win.height - 1);
	return (sp->x0 < sp->x1 && sp->y0 < sp->y1);
}

void	sprite_draw(t_game *g, t_sprite *sp, t_image *tex)
{
	int		col;
	double	*zbuf;

	if (!g || !sp || !tex || !tex->img_addr)
		return ;
	if (!g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	zbuf = g->ray.z_buffer;
	col = sp->x0;
	while (col < sp->x1)
	{
		if (sp->depth < zbuf[col])
			sprite_draw_col(g, sp, col, tex);
		col++;
	}
}
