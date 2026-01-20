/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:32:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/20 17:25:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

// int	game_loop(t_game *g)
// {
// 	(void)g;
// 	if (g->key.esc)
// 		exit_game(EXIT_QUIT, g);
// 	// clear_framebuffer(g);
// 	render_3d(g);
// 	mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr, g->render.img_ptr, 0, 0);
// 	return (0);
// }

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g);
	setup_map_grid(g); // inicializar o mapa 3D
	init_player_from_map(g); // inicializar a posição do player a partir do mapa
	g->render.width = g->render.width;
	g->render.height = g->render.height;
	g->ray.z_buffer = malloc(sizeof(double) * g->render.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
		
}
