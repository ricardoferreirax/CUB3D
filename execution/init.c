/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:09 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/17 21:31:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

// int	game_loop(t_game *g)
// {
// 	if (g->key.esc)
// 		exit_game(EXIT_QUIT, g);
// 	clear_framebuffer(g);
// 	render_3d(g);
// 	mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr, g->win.frame_buffer.img_ptr, 0, 0);
// 	return (0);
// }

void	start_execution(t_game *game)
{
	if (!game || !game->mlx_ptr || !game->win.win_ptr
		|| !game->win.frame_buffer.img_ptr || !game->win.frame_buffer.img_addr)
		exit_game(EXIT_MLX, game);
	// init_3d(game);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	// mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
}
