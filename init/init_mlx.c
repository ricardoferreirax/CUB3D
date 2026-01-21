/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:53:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/21 21:18:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

// void	init_window(t_game *s)
// {
// 	s->win.ntilesx = 28;
// 	s->win.ntilesy = 25;
// 	s->win.width = 8 * 28;
// 	s->win.height = 8 * 25;
// 	s->win.win_ptr = mlx_new_window(s->mlx_ptr, s->win.width, s->win.height, "Pac-Man");
// 	if (!s->win.win_ptr)
// 		exit_game(EXIT_MLX, s);
// }

void	init_render(t_game *g)
{
	g->render.width = g->win.width;
	g->render.height = g->win.height;
	g->render.img_ptr = mlx_new_image(g->mlx_ptr, g->render.width, g->render.height);
	if (!g->render.img_ptr)
		exit_game(EXIT_MLX, g);
	g->render.img_addr = mlx_get_data_addr(g->render.img_ptr,
			&g->render.bpp, &g->render.l_len, &g->render.endian);
	if (!g->render.img_addr)
		exit_game(EXIT_MLX, g);
}

void	init_mlx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		exit_game(EXIT_MLX, g);

	init_window(g);
	init_render(g);
}
