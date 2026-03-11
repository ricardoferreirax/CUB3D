/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:39:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 17:19:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "hooks.h"
#include "../player/player3D.h"

void	center_mouse(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		return ;
	mlx_mouse_move(g->mlx_ptr, g->win.win_ptr,
		g->win.width / 2, g->win.height / 2);
}

int	handle_mouse_move(int x, int y, t_game *g)
{
	int		center_x;
	int		delta_x;
	double	angle;

	(void)y;
	if (!g || g->state == MENU)
		return (0);
	if (g->key.mouse_lock)
	{
		g->key.mouse_lock = 0;
		return (0);
	}
	center_x = g->win.width / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	angle = delta_x * MOUSE_SENS;
	player_rotate(g, angle);
	g->key.mouse_lock = 1;
	center_mouse(g);
	return (0);
}
