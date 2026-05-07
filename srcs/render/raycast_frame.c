/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 15:47:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"
#include "../textures/textures3D.h"

static int	register_center_hit(t_game *g, int col, int found)
{
	char	tile;

	if (!g || found)
		return (found);
	if (col != (g->win.width - 1) / 2 && col != g->win.width / 2)
		return (found);
	tile = map_get_tile(g, g->ray.map_y, g->ray.map_x);
	if (tile == OPEN_SPACE || tile == VOID)
		return (found);
	g->player.target_map.x = g->ray.map_x;
	g->player.target_map.y = g->ray.map_y;
	g->player.target_tile = tile;
	if (g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		g->player.target_wall_dir = 'W';
	else if (g->ray.hit_side == 0)
		g->player.target_wall_dir = 'E';
	else if (g->ray.ray_dir_y < 0)
		g->player.target_wall_dir = 'N';
	else
		g->player.target_wall_dir = 'S';
	g->player.target_dist = g->ray.perp_wall_dist;
	return (1);
}

void	ray_draw_range(t_game *g)
{
	int	col_height;

	col_height = (int)((double)g->win.height / g->ray.perp_wall_dist);
	if (col_height < 1)
		col_height = 1;
	g->ray.line_h = col_height;
	g->ray.draw_start = g->win.height / 2 - col_height / 2;
	g->ray.draw_end = g->win.height / 2 + col_height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

void	ray_init_steps(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos.tile_pos.x - g->ray.map_x)
			* g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + TILE_SIZE_3D
				- g->player.pos.tile_pos.x) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos.tile_pos.y - g->ray.map_y)
			* g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + TILE_SIZE_3D
				- g->player.pos.tile_pos.y) * g->ray.delta_dist_y;
	}
}

void	ray_init(t_game *g, int col)
{
	double	cam_x;

	cam_x = 2.0 * col / (double)g->win.width - 1.0;
	g->ray.camera_x = cam_x;
	g->ray.ray_dir_x = g->player.dir.x + g->player.plane.x * cam_x;
	g->ray.ray_dir_y = g->player.dir.y + g->player.plane.y * cam_x;
	g->ray.map_x = (int)g->player.pos.tile_pos.x;
	g->ray.map_y = (int)g->player.pos.tile_pos.y;
	g->ray.hit = 0;
	g->ray.hit_side = 0;
	g->ray.hit_tile = VOID;
	if (g->ray.ray_dir_x == 0.0)
		g->ray.delta_dist_x = 1e30;
	else
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (g->ray.ray_dir_y == 0.0)
		g->ray.delta_dist_y = 1e30;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

void	raycast_frame(t_game *g)
{
	int	col;
	int	center_hit;

	if (!g)
		return ;
	col = -1;
	center_hit = 0;
	while (++col < g->win.width)
	{
		ray_init(g, col);
		ray_init_steps(g);
		if (raycast_find_wall(g))
		{
			ray_perp_wall_distance(g);
			ray_draw_range(g);
			draw_wall_column(g, col);
			g->ray.z_buffer[col] = g->ray.perp_wall_dist;
			center_hit = register_center_hit(g, col, center_hit);
		}
	}
}
