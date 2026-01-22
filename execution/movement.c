/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:52:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/22 15:06:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static int	is_wall_tile(t_game *g, int map_y, int map_x)
{
	if (map_y < 0 || map_x < 0 || map_y >= g->map.height || map_x >= g->map.width)
		return (1);
	if (!g->map.grid || !g->map.grid[map_y])
		return (1);
	return (g->map.grid[map_y][map_x] == '1'); // WALL
}

static void	try_move(t_game *g, double next_x, double next_y)
{
	if (!is_wall_tile(g, (int)g->player.pos_y, (int)next_x))
		g->player.pos_x = next_x;
	if (!is_wall_tile(g, (int)next_y, (int)g->player.pos_x))
		g->player.pos_y = next_y;
}

static void	rotate_view(t_game *g, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(rot) - g->player.dir_y * sin(rot);
	g->player.dir_y = old_dir_x * sin(rot) + g->player.dir_y * cos(rot);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(rot) - g->player.plane_y * sin(rot);
	g->player.plane_y = old_plane_x * sin(rot) + g->player.plane_y * cos(rot);
}

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
