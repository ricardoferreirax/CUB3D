/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:39:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/12 17:50:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../player/player3D.h"
#include "hooks.h"

void	center_mouse(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		return ;
	mlx_mouse_move(g->mlx_ptr, g->win.win_ptr,
		g->win.width / 2, g->win.height / 2);
}

void	toggle_mouse_capture(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		return ;
	g->key.mouse_captured = !g->key.mouse_captured;
	if (g->key.mouse_captured)
	{
		g->key.mouse_hidden = 1;
		g->key.mouse_lock = 1;
		mlx_mouse_hide(g->mlx_ptr, g->win.win_ptr);
		center_mouse(g);
	}
	else
	{
		g->key.mouse_hidden = 0;
		g->key.mouse_lock = 0;
		mlx_mouse_show(g->mlx_ptr, g->win.win_ptr);
	}
}

int	handle_mouse_move(int x, int y, t_game *g)
{
	int		center_x;
	int		delta_x;
	double	angle;

	(void)y;
	if (!g || g->state == MENU || g->mode == MODE_PACMAN)
		return (0);
	if (!g->key.mouse_captured)
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
