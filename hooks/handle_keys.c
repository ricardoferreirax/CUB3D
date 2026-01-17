/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:59:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/17 20:49:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	print_help(void)
{
	ft_putstr("\nCommands:\n");
	ft_putstr(" - Move: W A S D\n");
	ft_putstr(" - Rotate: Left / Right\n");
	ft_putstr(" - ESC: quit\n");
}

int	handle_key_press(int keycode, t_game *g)
{
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
	else if (keycode == KEY_H)
		print_help();
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
	return (0);
}
