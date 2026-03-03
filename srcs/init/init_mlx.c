/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:53:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:52:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

void	init_framebuffer(t_game *g)
{
	g->win.frame_buffer.img_ptr = mlx_new_image(g->mlx_ptr, g->win.width, g->win.height);
	if (!g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g, "init_framebuffer() was unable to create img_ptr");
	g->win.frame_buffer.img_addr = mlx_get_data_addr(g->win.frame_buffer.img_ptr,&g->win.frame_buffer.bpp,
		&g->win.frame_buffer.l_len,&g->win.frame_buffer.endian);
	if (!g->win.frame_buffer.img_addr)
		exit_game(EXIT_MLX, g, "init_framebufer() was unable to create img_addr");
	g->win.frame_buffer.width = g->win.width;
	g->win.frame_buffer.height = g->win.height;
}

void	init_window(t_game *g)
{
	g->win.ntilesx = xtile(g->map.grid);
	g->win.ntilesy = ytile(g->map.grid);
	g->win.width = 1920;
	g->win.height = 1080;
	g->win.win_ptr = mlx_new_window(g->mlx_ptr, g->win.width, g->win.height, "Pac-Man");
	if (!g->win.win_ptr)
		exit_game(EXIT_MLX, g, "init_window() was unable to create win_ptr");
}

void	init_minilib(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		exit_game(EXIT_MLX, g, "init_minilib() was unable to create mlx_ptr");
	init_window(g);
	init_framebuffer(g);
}
