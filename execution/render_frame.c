/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/27 20:28:06 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	apply_input(t_game *g)
{
	if (!g)
		return ;
	player_rotation_controller(g);
	movement_controller(g);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game);
	apply_input(game);
	fill_ceiling_color(&game->win.frame_buffer, game->map.ceiling_color, 0);
	fill_floor_color(&game->win.frame_buffer, game->map.floor_color, 0);
	process_raycasting(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr, game->win.frame_buffer.img_ptr, 0, 0);
}

