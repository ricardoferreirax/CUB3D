/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:17:49 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 21:32:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

#define DEBUG_CELL 12
#define DEBUG_OFF_X 20
#define DEBUG_OFF_Y 20
#define DEBUG_RAY_STEP 20
#define DEBUG_COLOR_BG 0x000000
#define DEBUG_COLOR_WALL 0xFFFFFF
#define DEBUG_COLOR_GRID 0x444444
#define DEBUG_COLOR_RAY 0x00FF00
#define DEBUG_COLOR_PLAYER 0xFFFF00
#define DEBUG_COLOR_HIT 0xFF0000

static int	abs_i(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	debug_pixel_put(t_game *g, int x, int y, int color)
{
	if (!g)
		return ;
	if (x < 0 || x >= g->win.width || y < 0 || y >= g->win.height)
		return ;
	ft_pixel_put(&g->win.frame_buffer, x, y, color);
}

static void	draw_debug_dot(t_game *g, t_point p, int radius, int color)
{
	int	i;
	int	j;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			debug_pixel_put(g, p.x + j, p.y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_debug_line(t_game *g, t_point a, t_point b, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs_i(b.x - a.x);
	dy = abs_i(a.y - b.y);
	sx = -1;
	if (a.x < b.x)
		sx = 1;
	sy = -1;
	if (a.y < b.y)
		sy = 1;
	err = dx - dy;
	while (1)
	{
		debug_pixel_put(g, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			a.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			a.y += sy;
		}
	}
}

static void	draw_debug_rect(t_game *g, int x, int y, int color)
{
	int	sx;
	int	sy;
	int	start_x;
	int	start_y;

	start_x = DEBUG_OFF_X + x * DEBUG_CELL;
	start_y = DEBUG_OFF_Y + y * DEBUG_CELL;
	sy = 0;
	while (sy < DEBUG_CELL)
	{
		sx = 0;
		while (sx < DEBUG_CELL)
		{
			debug_pixel_put(g, start_x + sx, start_y + sy, color);
			sx++;
		}
		sy++;
	}
}

static void	draw_debug_grid(t_game *g)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_x = DEBUG_OFF_X + g->map.width * DEBUG_CELL;
	max_y = DEBUG_OFF_Y + g->map.height * DEBUG_CELL;
	x = DEBUG_OFF_X;
	while (x <= max_x)
	{
		y = DEBUG_OFF_Y;
		while (y <= max_y)
		{
			debug_pixel_put(g, x, y, DEBUG_COLOR_GRID);
			y++;
		}
		x += DEBUG_CELL;
	}
	y = DEBUG_OFF_Y;
	while (y <= max_y)
	{
		x = DEBUG_OFF_X;
		while (x <= max_x)
		{
			debug_pixel_put(g, x, y, DEBUG_COLOR_GRID);
			x++;
		}
		y += DEBUG_CELL;
	}
}

static void	draw_debug_map(t_game *g)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			tile = map_get_tile(g, y, x);
			if (map_tile_type(tile, TILE_SOLID) || tile == GATE)
				draw_debug_rect(g, x, y, DEBUG_COLOR_WALL);
			else
				draw_debug_rect(g, x, y, DEBUG_COLOR_BG);
			x++;
		}
		y++;
	}
	draw_debug_grid(g);
}

static int	cast_debug_ray(t_game *g, int col, t_raycasting *out)
{
	t_raycasting	saved;

	if (!g || !out)
		return (0);
	saved = g->ray;
	ray_init(g, col);
	ray_init_steps(g);
	if (raycast_dda(g))
	{
		ray_perp_wall_distance(g);
		ray_draw_range(g);
		*out = g->ray;
		g->ray = saved;
		return (1);
	}
	g->ray = saved;
	return (0);
}

static void	draw_debug_rays(t_game *g)
{
	t_raycasting	ray;
	t_point			start;
	t_point			end;
	double			hit_x;
	double			hit_y;
	int				col;

	start.x = DEBUG_OFF_X + (int)(g->player.pos_x * DEBUG_CELL);
	start.y = DEBUG_OFF_Y + (int)(g->player.pos_y * DEBUG_CELL);
	col = 0;
	while (col < g->win.width)
	{
		if (cast_debug_ray(g, col, &ray))
		{
			hit_x = g->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
			hit_y = g->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
			end.x = DEBUG_OFF_X + (int)(hit_x * DEBUG_CELL);
			end.y = DEBUG_OFF_Y + (int)(hit_y * DEBUG_CELL);
			draw_debug_line(g, start, end, DEBUG_COLOR_RAY);
			draw_debug_dot(g, end, 1, DEBUG_COLOR_HIT);
		}
		col += DEBUG_RAY_STEP;
	}
	draw_debug_dot(g, start, 2, DEBUG_COLOR_PLAYER);
}

void	render_raycast_debug(t_game *g)
{
	if (!g)
		return ;
	draw_debug_map(g);
	draw_debug_rays(g);
}
