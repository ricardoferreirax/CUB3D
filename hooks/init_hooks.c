/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:34:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 15:34:34 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	init_hooks(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		exit_game(EXIT_MLX, g);
	mlx_hook(g->win.win_ptr, 2, 1L << 0, handle_key_press, g);
	mlx_hook(g->win.win_ptr, 3, 1L << 1, handle_key_release, g);
	mlx_hook(g->win.win_ptr, 17, 0, handle_close, g);
	mlx_loop_hook(g->mlx_ptr, game_loop, g);
}
