/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:32:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/25 13:57:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		exit_game(EXIT_MLX, g);
	setup_map_grid(g);
	init_player_from_map(g);
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
}
