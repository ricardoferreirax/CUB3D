/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 21:31:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	ray_draw_range(t_game *g)
{
	int	col_height;

	col_height = (int)((double)g->win.height / g->ray.perp_wall_dist);
	if (col_height < 1)
		col_height = 1;
	g->ray.line_h = col_height;
	g->ray.draw_start = g->win.height / 2 - col_height / 2;
	g->ray.draw_end = g->win.height / 2 + col_height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

void ray_perp_wall_distance(t_game *g) 
{ 
	if (g->ray.hit_side == 0) 
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x; 
	else 
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y; 
	if (g->ray.perp_wall_dist < 1e-6) 
 		g->ray.perp_wall_dist = 1e-6; 
}

void	ray_init_steps(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos.tile_pos.x - g->ray.map_x)
			* g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + TILE_SIZE_3D - g->player.pos.tile_pos.x)
			* g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos.tile_pos.y - g->ray.map_y)
			* g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + TILE_SIZE_3D - g->player.pos.tile_pos.y)
			* g->ray.delta_dist_y;
	}
}

void	ray_init(t_game *g, int col)
{
	double	cam_x;


	cam_x = 2.0 * col / (double)g->win.width - 1.0; // 
	g->ray.camera_x = cam_x; // 
	g->ray.ray_dir_x = g->player.dir.x + g->player.plane.x * cam_x; // direção do raio no eixo x
	g->ray.ray_dir_y = g->player.dir.y + g->player.plane.y * cam_x; // direção do raio no eixo y
	g->ray.map_x = (int)g->player.pos.tile_pos.x; // coordenada do mapa (tile) onde o player está no eixo x
	g->ray.map_y = (int)g->player.pos.tile_pos.y; // coordenada do mapa (tile) onde o player está no eixo y
	g->ray.hit = 0; // flag que indica se o raio bateu numa parede. Começa em 0 e fica 1 quando bate numa parede
	g->ray.hit_side = 0; // lado da parede que foi atingido 0 para x 1 para y
	g->ray.hit_tile = VOID; // o tile atingido é void se for diferente de VOID o raio atingiu um tile sólido e guardo o id do tile atingido
	if (g->ray.ray_dir_x == 0.0) // se a direção do raio no eixo x for 0
		g->ray.delta_dist_x = 1e30; // a distância para o próximo grid no eixo x é infinita. Evita a divisao por zero e garante que o raio só vai cruzar grids no eixo y
	else // se a direção do raio no eixo x for diferente de 0
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x); // É calculada a hipotenusa do triângulo formado pelo step no eixo x (1) e o step no eixo y (delta_dist_y) multiplicada pela direção do raio no eixo x. O resultado é a distância que o raio percorre para cruzar uma grid no eixo x.
	if (g->ray.ray_dir_y == 0.0)
		g->ray.delta_dist_y = 1e30;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

void	raycast_frame(t_game *g)
{
	int	col;
	int	center_hit;

	if (!g)
		return ;
	col = -1;
	center_hit = 0; // flag que regista se o hit do centro da tela já foi registado para evitar múltiplos registros numa mesma parede
	while (++col < g->win.width)
	{
		ray_init(g, col); // inicializa os valores do ray para a coluna atual
		ray_init_steps(g); // calcula os steps e as distâncias iniciais para o DDA
		if (raycast_dda(g)) // se bateu numa parede renderiza a coluna caso contrario passa para a próxima
		{
			ray_perp_wall_distance(g); // calcula a distância perpendicular da parede
			ray_draw_range(g); // calcula o range de pixels a desenhar para a parede
			render_wall_column(g, col); // renderiza a coluna da parede
			g->ray.z_buffer[col] = g->ray.perp_wall_dist;
			center_hit = register_center_hit(g, col, center_hit);
		}
	}
}
