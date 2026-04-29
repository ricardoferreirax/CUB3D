/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:59:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 19:44:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "hooks.h"

static int	handle_menu_key(int keycode, t_game *g)
{
	if (keycode == 65307)
		handle_close(g);
	else if (keycode == 49 || g->key.controller_start == 1)
		start_game_mode(g, MODE_PACMAN);
	else if (keycode == 50)
		start_game_mode(g, MODE_CUBE);
	return (0);
}

int	handle_key_press(int keycode, t_game *g)
{
	if (!g)
		return (0);
	if (g->state == MENU)
		return (handle_menu_key(keycode, g));
	if (keycode == 65307)
		g->key.esc = 1;
	else if (keycode == 119)
		g->key.w = 1;
	else if (keycode == 97)
		g->key.a = 1;
	else if (keycode == 115)
		g->key.s = 1;
	else if (keycode == 100)
		g->key.d = 1;
	else if (keycode == 65361)
		g->key.left = 1;
	else if (keycode == 65363)
		g->key.right = 1;
	else if (keycode == 65362)
		g->key.up = 1;
	else if (keycode == 65364)
		g->key.down = 1;
	else if (keycode == 101 && g->mode == MODE_CUBE)
		g->key.e = 1;
	else if (keycode == 109)
	{
		if (g->key.mouse_hidden)
		{
			mlx_mouse_show(g->mlx_ptr, g->win.win_ptr);
			g->key.mouse_hidden = 0;
		}
		else
		{
			mlx_mouse_hide(g->mlx_ptr, g->win.win_ptr);
			g->key.mouse_hidden = 1;
			g->key.mouse_lock = 1;
			center_mouse(g);
		}
	}
	return (0);
}

int	handle_key_release(int keycode, t_game *g)
{
	if (keycode == 65307)
		g->key.esc = 0;
	else if (keycode == 119)
		g->key.w = 0;
	else if (keycode == 97)
		g->key.a = 0;
	else if (keycode == 115)
		g->key.s = 0;
	else if (keycode == 100)
		g->key.d = 0;
	else if (keycode == 65361)
		g->key.left = 0;
	else if (keycode == 65363)
		g->key.right = 0;
	else if (keycode == 65362)
		g->key.up = 0;
	else if (keycode == 65364)
		g->key.down = 0;
	else if (keycode == 101)
	{
		g->key.e = 0;
		g->key.e_lock = 0;
	}
	return (0);
}
