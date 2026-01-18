/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:32:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 15:51:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	game_loop(t_game *g)
{
	if (g->key.esc)
		exit_game(EXIT_QUIT, g);
	// clear_framebuffer(g);
	// render_3d(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr,
		g->win.frame_buffer.img_ptr, 0, 0);
	return (0);
}

void	init_raycasting_runtime(t_game *game)
{
	game->ray.z_buffer = malloc(sizeof(double) * game->win.width);
	if (!game->ray.z_buffer)
		exit_game(EXIT_MALLOC, game);
}

void	start_execution(t_game *game)
{
	if (!game || !game->mlx_ptr || !game->win.win_ptr)
		exit_game(EXIT_MLX, game);
	init_map_dims(game);
	init_raycasting_runtime(game);
	init_hooks(game);
	mlx_loop(game->mlx_ptr);
}

