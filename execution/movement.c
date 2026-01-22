/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:52:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/22 14:57:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

void	apply_input(t_game *g)
{
	double	move;
	double	rot;
	
	move = 0.06;
	rot = 0.05;
	if (g->key.left)
		rotate_view(g, -rot);
	if (g->key.right)
		rotate_view(g, rot);
	if (g->key.w)
		try_move(g, g->player.pos_x + g->player.dir_x * move,
			g->player.pos_y + g->player.dir_y * move);
	if (g->key.s)
		try_move(g, g->player.pos_x - g->player.dir_x * move,
			g->player.pos_y - g->player.dir_y * move);
	if (g->key.a)
		try_move(g, g->player.pos_x - g->player.plane_x * move,
			g->player.pos_y - g->player.plane_y * move);
	if (g->key.d)
		try_move(g, g->player.pos_x + g->player.plane_x * move,
			g->player.pos_y + g->player.plane_y * move);
}
