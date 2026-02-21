/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 21:39:47 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	clear_sprite_z(t_game *g)
{
	int		i;
	int		n;

	if (!g || !g->ray.sprite_z)
		return ;
	n = g->win.width * g->win.height;
	i = 0;
	while (i < n)
	{
		g->ray.sprite_z[i] = 1e30;
		i++;
	}
}

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
	render_ceiling_texture(game);
	render_floor_texture(game);
	process_raycasting(game);
	handle_gate_input(game);
	clear_sprite_z(game);
	render_all_sprites(game);
	render_minimap_test(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr, game->win.frame_buffer.img_ptr, 0, 0);
}
