/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:12:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/08 14:16:08 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
# include <linux/input.h>
#include "../../Pac_Struct.h"

static	void	d_pad_handler(t_game *game, struct input_event event)
{
	if (event.code == ABS_HAT0X)
	{
		game->key.a = (event.value == -1);
		game->key.d = (event.value == 1);
	}
	else if (event.code == ABS_HAT0Y)
	{
		game->key.w = (event.value == -1);
		game->key.s = (event.value == 1);
	}
	else if (event.code == ABS_RZ)
		game->key.e = (event.value > 100);
}

static	void	face_button_handler(t_game *game, struct input_event event)
{
	if (event.code == BTN_SOUTH)
		game->key.down = event.value;
	else if (event.code == BTN_NORTH)
		game->key.up = event.value;
	else if (event.code == BTN_WEST)
		game->key.left = event.value;
	else if (event.code == BTN_EAST)
		game->key.right = event.value;
	else if (event.code == BTN_TR)
		game->key.k = event.value;
	else if (event.code == BTN_START)
		game->key.controller_start = event.value;
}

void	controller_player(t_game *game)
{
	struct input_event	event;

	if (game->controller_fd < 0)
		return ;
	while (read(game->controller_fd, &event, sizeof(event)) > 0)
	{
		if (event.type != EV_KEY && event.type != EV_ABS)
			continue ;
		if (event.type == EV_KEY)
			face_button_handler(game, event);
		if (event.type == EV_ABS)
			d_pad_handler(game, event);
	}
}
