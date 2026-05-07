/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:15:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 15:52:29 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	set_plane(t_game *g, t_fc *plane, double dist)
{
	double	left_x;
	double	left_y;

	// componente x do vetor direção do raio que passa pelo canto esquerdo da tela
	// componente y do vetor direção do raio que passa pelo canto esquerdo da tela
	left_x = g->player.dir.x - g->player.plane.x;
	// direção do raio para o canto esquerdo da tela no eixo x
	left_y = g->player.dir.y - g->player.plane.y;
	// direção do raio para o canto esquerdo da tela no eixo y
	plane->step_x = dist * (2.0 * g->player.plane.x) / g->win.width;
	// avanço no eixo x no mundo para cada pixel da linha
	plane->step_y = dist * (2.0 * g->player.plane.y) / g->win.width;
	// avanço no eixo y no mundopara cada pixel da linha
	plane->pos_x = g->player.pos.tile_pos.x + dist * left_x;
	plane->pos_y = g->player.pos.tile_pos.y + dist * left_y;
}

static void	draw_plane_row(t_game *g, t_fc *plane, t_image *tex, int row)
{
	unsigned int	*pixels;
	int				col;
	int				tex_x;
	int				tex_y;
	int				stride;

	pixels = (unsigned int *)(g->win.frame_buffer.img_addr + row
			* g->win.frame_buffer.l_len);
	col = 0;
	stride = tex->l_len / 4;
	if (!tex->img_addr)
	{
		while (col < g->win.width)
		{
			pixels[col] = 128;
			col++;
		}
	}
	else
	{
		tex->data = (unsigned int *)tex->img_addr;
		while (col < g->win.width)
		{
			tex_x = ((int)(plane->pos_x * tex->width) % tex->width + tex->width)
				% tex->width;
			tex_y = ((int)(plane->pos_y * tex->height) % tex->height
					+ tex->height) % tex->height;
			if (!tex->data)
				pixels[col] = 128;
			else
				pixels[col] = tex->data[tex_y * stride + tex_x];
			plane->pos_x += plane->step_x;
			plane->pos_y += plane->step_y;
			col++;
		}
	}
}

void	render_floor_texture(t_game *g)
{
	int		row;
	double	dist;
	double	screen_dist;

	t_fc plane; // guarda os dados da linha atual do floor
	// linha atual do frame buffer no ecrã onde os pixels do chão vão ser desenhados
	// distância perpendicular do player ao plano do chão para a linha atual do chão a ser desenhada
	// distância vertical da linha atual do chão ao centro da tela
	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.floor_img.img_ptr)
	{
		fill_floor_color(&g->win.frame_buffer, g->map.floor_color, 0);
		return ;
	}
	row = g->win.height / 2 + FLOOR_START_OFFSET;
	// começa a desenhar o floor a partir do centro da tela
	while (row < g->win.height)
	// percorre todas as linhas do floor até ao final/fundo da tela
	{
		screen_dist = row - g->win.height * 0.5;
		// calcula a distância vertical da linha atual do chão ao centro da tela
		if (screen_dist < FLOOR_MIN_DIST)
			// evita valores demasiado pequenos
			screen_dist = FLOOR_MIN_DIST;
		dist = (g->win.height * 0.5) / screen_dist;
		// converte a distância na tela para a distancia perpendicular no mundo
		set_plane(g, &plane, dist);
		// prepara a posição inicial e os steps da linha atual do chão a ser desenhada
		draw_plane_row(g, &plane, &g->tex.floor_img, row);
		// desenha a linha atual do chão com a textura do chão
		row++;
		// passa para a próxima linha do chão a ser desenhada
	}
}

void	render_ceiling_texture(t_game *g)
{
	t_fc	plane;
	int		row;
	double	dist;
	double	screen_dist;

	if (!g || !g->win.frame_buffer.img_addr)
		return ;
	if (!g->tex.ceiling_img.img_ptr)
	{
		fill_ceiling_color(&g->win.frame_buffer, g->map.ceiling_color, 0);
		return ;
	}
	row = 0;
	while (row < (g->win.height / 2) - CEILING_CENTER_MARGIN)
	{
		screen_dist = (g->win.height * 0.5 + CEILING_HORIZON) - row;
		if (screen_dist < CEILING_MIN_SCREEN_DIST)
			screen_dist = CEILING_MIN_SCREEN_DIST;
		dist = (g->win.height * 0.5 * CEILING_DIST) / screen_dist;
		set_plane(g, &plane, dist);
		draw_plane_row(g, &plane, &g->tex.ceiling_img, row);
		row++;
	}
}
