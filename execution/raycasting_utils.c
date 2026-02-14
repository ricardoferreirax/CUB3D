/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:48:50 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:50:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static int	is_center_column(t_game *g, int x)
{
	int	c0;
	int	c1;

	c0 = (g->win.width - 1) / 2;
	c1 = g->win.width / 2;
	return (x == c0 || x == c1);
}

static int	is_center_hit(t_game *g, int already_found, int screen_x)
{
	char	tile;

	if (!g || already_found)
		return (0);
	if (!is_center_column(g, screen_x))
		return (0);
	tile = map_get_tile(g, g->ray.map_y, g->ray.map_x);
	if (tile == OPEN_SPACE || tile == VOID)
		return (0);
	return (1);
}

int	register_center_hit(t_game *g, int screen_x, int hit_found)
{
	char	tile;

	if (!is_center_hit(g, hit_found, screen_x))
		return (hit_found);
	tile = map_get_tile(g, g->ray.map_y, g->ray.map_x);
	g->player.target_map_x = g->ray.map_x;
	g->player.target_map_y = g->ray.map_y;
	g->player.target_tile = tile;
	if (g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		g->player.target_wall_dir = 'W';
	else if (g->ray.hit_side == 0)
		g->player.target_wall_dir = 'E';
	else if (g->ray.hit_side == 1 && g->ray.ray_dir_y < 0)
		g->player.target_wall_dir = 'N';
	else
		g->player.target_wall_dir = 'S';
	g->player.target_dist = g->ray.perp_wall_dist;
	return (1);
}
