/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/24 19:56:14 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	draw_vertical_line(t_game *g, int x)
{
	int	y;
	int	color;

	color = 0x00FF0000; // vermelho
	if (g->ray.hit_side == 1)
		color = 0x00AA0000; // darker >:)
	y = g->ray.draw_start;
	while (y <= g->ray.draw_end)
	{
		put_pixel(&g->win.frame_buffer, x, y, color);
		y++;
	}
}

static void	calc_draw_limits(t_game *g)
{
	int	line_h;

	line_h = (int)(g->win.height / g->ray.perp_wall_dist);
	g->ray.draw_start = -line_h / 2 + g->win.height / 2;
	g->ray.draw_end = line_h / 2 + g->win.height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

static void	calc_wall_distance(t_game *g)
{
	if (g->ray.hit_side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else // hit_side == 1
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	if (g->ray.perp_wall_dist < 1e-6) // evitar div/0 e valores negativos :3
		g->ray.perp_wall_dist = 1e-6;
}

static void	perform_dda(t_game *g)
{
	int	wall_hit;

	wall_hit = 0;
	while (!wall_hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_dist_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.hit_side = 0; // hit numa parede vertical (X)
		}
		else // side_dist_y <= side_dist_x
		{
			g->ray.side_dist_y += g->ray.delta_dist_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.hit_side = 1; // hit numa parede horizontal (Y)
		}
		if (map_tile(g, g->ray.map_y, g->ray.map_x) == WALL)
			wall_hit = 1;
	}
}

static void	calculate_dda_step(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos_x - g->ray.map_x) * g->ray.delta_dist_x;
	}
	else // ray_dir_x >= 0
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - g->player.pos_x) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos_y - g->ray.map_y) * g->ray.delta_dist_y;
	}
	else // ray_dir_y >= 0
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - g->player.pos_y) * g->ray.delta_dist_y;
	}
}

static void	init_ray(t_game *g, int x)
{
	g->ray.camera_x = 2.0 * x / (double)g->win.width - 1.0;
	g->ray.ray_dir_x = g->player.dir_x + g->player.plane_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->player.dir_y + g->player.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)g->player.pos_x;
	g->ray.map_y = (int)g->player.pos_y;
	if (g->ray.ray_dir_x == 0)
		g->ray.delta_dist_x = 1e30;
	else
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (g->ray.ray_dir_y == 0)
		g->ray.delta_dist_y = 1e30;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

void	process_raycasting(t_game *g)
{
	int	screen_x;
	int	hit_found;

	screen_x = 0;
	hit_found = 0;
	render_background(g);
	while (screen_x < g->win.width)
	{
		init_ray(g, screen_x);
		calculate_dda_step(g);
		perform_dda(g);
		calc_wall_distance(g);
		calc_draw_limits(g);
		draw_vertical_line(g, screen_x);
		hit_found = register_center_hit(g, screen_x, hit_found);
		g->ray.z_buffer[screen_x] = g->ray.perp_wall_dist;
		screen_x++;
	}
}
