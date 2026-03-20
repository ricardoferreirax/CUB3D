/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:59:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/25 15:38:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "hooks.h"

static int	handle_menu_key(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		handle_close(g);
	else if (keycode == KEY_1)
		start_game_mode(g, MODE_PACMAN);
	else if (keycode == KEY_2)
		start_game_mode(g, MODE_CUBE);
	return (0);
}

int	handle_key_press(int keycode, t_game *g)
{
	if (!g)
		return (0);
	if (g->state == MENU)
		return (handle_menu_key(keycode, g));
	if (keycode == KEY_ESC)
		g->key.esc = 1;
	else if (keycode == KEY_W)
		g->key.w = 1;
	else if (keycode == KEY_A)
		g->key.a = 1;
	else if (keycode == KEY_S)
		g->key.s = 1;
	else if (keycode == KEY_D)
		g->key.d = 1;
	else if (keycode == KEY_LEFT)
		g->key.left = 1;
	else if (keycode == KEY_RIGHT)
		g->key.right = 1;
	else if (keycode == KEY_E && g->mode == MODE_CUBE)
		g->key.e = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		g->key.esc = 0;
	else if (keycode == KEY_W)
		g->key.w = 0;
	else if (keycode == KEY_A)
		g->key.a = 0;
	else if (keycode == KEY_S)
		g->key.s = 0;
	else if (keycode == KEY_D)
		g->key.d = 0;
	else if (keycode == KEY_LEFT)
		g->key.left = 0;
	else if (keycode == KEY_RIGHT)
		g->key.right = 0;
	else if (keycode == KEY_E)
	{
		g->key.e = 0;
		g->key.e_lock = 0;
	}
	return (0);
}
