/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:32:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 21:13:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	game_loop(t_game *g)
{
	if (g->key.esc)
		exit_game(EXIT_QUIT, g);
	// clear_framebuffer(g);
	render_3d(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr, g->render.img_ptr, 0, 0);
	return (0);
}

void	init_raycasting(t_game *g)
{
	g->ray.z_buffer = malloc(sizeof(double) * g->render.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
}

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g);
	init_map_3d(g); // inicializar o mapa 3D
	init_player_from_map(g); // inicializar a posição do player a partir do mapa
	init_raycasting(g);
	init_hooks(g);
	mlx_loop(g->mlx_ptr);
}
