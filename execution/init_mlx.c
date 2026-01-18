/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:53:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 16:00:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	init_window(t_game *s)
{
	s->win.ntilesx = 28;
	s->win.ntilesy = 25;
	s->win.width = 8 * 28;
	s->win.height = 8 * 25;
	s->win.win_ptr = mlx_new_window(s->mlx_ptr, s->win.width, s->win.height, "Pac-Man");
	if (!s->win.win_ptr)
		exit_game(EXIT_MLX, s);
	s->win.frame_buffer.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width, s->win.height);
	if (!s->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, s);
	s->win.frame_buffer.img_addr = mlx_get_data_addr(s->win.frame_buffer.img_ptr,
		&s->win.frame_buffer.bpp, &s->win.frame_buffer.l_len, &s->win.frame_buffer.endian);
	if (!s->win.frame_buffer.img_addr)
		exit_game(EXIT_MLX, s);
	s->win.frame_buffer.width = s->win.width;
	s->win.frame_buffer.height = s->win.height;
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_game(EXIT_MLX, game);
	init_window(game);
}
