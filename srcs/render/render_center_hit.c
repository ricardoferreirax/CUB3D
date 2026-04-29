/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_center_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:48:50 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/09 13:20:33 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

static char	get_hit_wall_dir(t_game *g)
{
	if (g->ray.hit_side == 0)
	{
		if (g->ray.ray_dir_x < 0)
			return ('W');
		return ('E');
	}
	if (g->ray.ray_dir_y < 0)
		return ('N');
	return ('S');
}

static int	is_screen_center(t_game *g, int col)
{
	return (col == (g->win.width - 1) / 2 || col == g->win.width / 2);
}

int	register_center_hit(t_game *g, int col, int found)
{
	char	tile;

	if (!g || found || !is_screen_center(g, col))
		return (found);
	tile = map_get_tile(g, g->ray.map_y, g->ray.map_x);
	if (tile == OPEN_SPACE || tile == VOID)

		return (found);
	g->player.target_map.x = g->ray.map_x;
	g->player.target_map.y = g->ray.map_y;
	g->player.target_tile = tile;
	g->player.target_wall_dir = get_hit_wall_dir(g);
	g->player.target_dist = g->ray.perp_wall_dist;
	return (1);
}
