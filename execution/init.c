/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:09 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/17 13:24:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	start_execution(t_game *game)
{
	if (!game || !game->mlx_ptr || !game->win.win_ptr
		|| !game->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, game);
	init_keys(game);
	init_view(game);
	// mlx_hook(game->win.win_ptr, 2, 1L << 0, on_key_press, game);
	// mlx_hook(game->win.win_ptr, 3, 1L << 1, on_key_release, game);
	// mlx_hook(game->win.win_ptr, 17, 0, on_close, game);
	// mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
}
