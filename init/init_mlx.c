/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:53:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/25 21:48:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

void	init_framebuffer(t_game *g)
{
	g->win.frame_buffer.img_ptr = mlx_new_image(g->mlx_ptr, g->win.width, g->win.height);
	if (!g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g);
	g->win.frame_buffer.img_addr = mlx_get_data_addr(g->win.frame_buffer.img_ptr,&g->win.frame_buffer.bpp,
		&g->win.frame_buffer.l_len,&g->win.frame_buffer.endian);
	if (!g->win.frame_buffer.img_addr)
		exit_game(EXIT_MLX, g);
	g->win.frame_buffer.width = g->win.width;
	g->win.frame_buffer.height = g->win.height;
}

void	init_window(t_game *g)
{
	g->win.ntilesx = 28;
	g->win.ntilesy = 25;
	g->win.width = 1200;
	g->win.height = 800;
	g->win.win_ptr = mlx_new_window(g->mlx_ptr, g->win.width, g->win.height, "Pac-Man");
	if (!g->win.win_ptr)
		exit_game(EXIT_MLX, g);
}

void	init_mlx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		exit_game(EXIT_MLX, g);
	init_window(g);
	init_framebuffer(g);
}

// void	init_render(t_game *g)
// {
// 	g->render.width = g->win.width;
// 	g->render.height = g->win.height;
// 	g->render.img_ptr = mlx_new_image(g->mlx_ptr, g->render.width, g->render.height);
// 	if (!g->render.img_ptr)
// 		exit_game(EXIT_MLX, g);
// 	g->render.img_addr = mlx_get_data_addr(g->render.img_ptr, &g->render.bpp, &g->render.l_len,
// 		&g->render.endian);
// 	if (!g->render.img_addr)
// 		exit_game(EXIT_MLX, g);
// }

