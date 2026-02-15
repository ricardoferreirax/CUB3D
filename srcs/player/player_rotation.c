/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:44:26 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/15 23:10:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static void	player_rotate_right(t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;
	double	c;
	double	s;

	c = cos(ROT_SPEED);
	s = sin(ROT_SPEED);

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * c - g->player.dir_y * s;
	g->player.dir_y = old_dir_x * s + g->player.dir_y * c;

	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * c - g->player.plane_y * s;
	g->player.plane_y = old_plane_x * s + g->player.plane_y * c;
}

static void	player_rotate_left(t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;
	double	c;
	double	s;

	c = cos(-ROT_SPEED);
	s = sin(-ROT_SPEED);

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * c - g->player.dir_y * s;
	g->player.dir_y = old_dir_x * s + g->player.dir_y * c;

	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * c - g->player.plane_y * s;
	g->player.plane_y = old_plane_x * s + g->player.plane_y * c;
}

void	player_rotation_controller(t_game *g)
{
	if (g->key.right)
		player_rotate_right(g);
	if (g->key.left)
		player_rotate_left(g);
}
