/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:17:49 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/04/23 14:25:10 by pfreire-         ###   ########.fr       */
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

static int	debug_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static t_point	debug_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

static void	debug_pixel_put(t_game *g, t_point p, int color)
{
	if (!g)
		return ;
	if (p.x < 0 || p.y < 0)
		return ;
	if (p.x >= g->win.width || p.y >= g->win.height)
		return ;
	ft_pixel_put(&g->win.frame_buffer, p.x, p.y, color);
}

static void	debug_fill(t_game *g, t_point p, int size, int color)
{
	t_point	i;

	i.y = 0;
	while (i.y < size)
	{
		i.x = 0;
		while (i.x < size)
		{
			debug_pixel_put(g, debug_point(p.x + i.x, p.y + i.y), color);
			i.x++;
		}
		i.y++;
	}
}

static t_point	debug_world_to_screen(double x, double y)
{
	t_point	p;

	p.x = DEBUG_OFF_X + (int)(x * DEBUG_CELL);
	p.y = DEBUG_OFF_Y + (int)(y * DEBUG_CELL);
	return (p);
}

static t_point	debug_line_delta(t_point a, t_point b)
{
	t_point	d;

	d.x = debug_abs(b.x - a.x);
	d.y = debug_abs(b.y - a.y);
	return (d);
}

static t_point	debug_line_step(t_point a, t_point b)
{
	t_point	s;

	s.x = -1;
	s.y = -1;
	if (a.x < b.x)
		s.x = 1;
	if (a.y < b.y)
		s.y = 1;
	return (s);
}

static void	debug_line_next(t_point *p, t_point d, t_point s, int *err)
{
	int	e2;

	e2 = (*err) * 2;
	if (e2 > -d.y)
	{
		*err -= d.y;
		p->x += s.x;
	}
	if (e2 < d.x)
	{
		*err += d.x;
		p->y += s.y;
	}
}

static void	debug_line(t_game *g, t_point a, t_point b, int color)
{
	t_point	d;
	t_point	s;
	t_point	p;
	int		err;

	p = a;
	d = debug_line_delta(a, b);
	s = debug_line_step(a, b);
	err = d.x - d.y;
	while (1)
	{
		debug_pixel_put(g, p, color);
		if (p.x == b.x && p.y == b.y)
			return ;
		debug_line_next(&p, d, s, &err);
	}
}

static int	debug_tile_color(t_game *g, int x, int y)
{
	char	tile;

	tile = map_get_tile(g, y, x);
	if (map_tile_type(tile, TILE_SOLID) || tile == GATE)
		return (DEBUG_COLOR_WALL);
	return (DEBUG_COLOR_BG);
}

static void	debug_draw_tile(t_game *g, int x, int y)
{
	t_point	p;
	int		color;

	p.x = DEBUG_OFF_X + x * DEBUG_CELL;
	p.y = DEBUG_OFF_Y + y * DEBUG_CELL;
	color = debug_tile_color(g, x, y);
	debug_fill(g, p, DEBUG_CELL, color);
}

static void	debug_draw_row(t_game *g, int y)
{
	int	x;

	x = 0;
	while (x < g->map.width)
	{
		debug_draw_tile(g, x, y);
		x++;
	}
}

static void	debug_draw_grid_v(t_game *g, t_point max)
{
	t_point	p;

	p.x = DEBUG_OFF_X;
	while (p.x <= max.x)
	{
		p.y = DEBUG_OFF_Y;
		while (p.y <= max.y)
		{
			debug_pixel_put(g, debug_point(p.x, p.y), DEBUG_COLOR_GRID);
			p.y++;
		}
		p.x += DEBUG_CELL;
	}
}

static void	debug_draw_grid_h(t_game *g, t_point max)
{
	t_point	p;

	p.y = DEBUG_OFF_Y;
	while (p.y <= max.y)
	{
		p.x = DEBUG_OFF_X;
		while (p.x <= max.x)
		{
			debug_pixel_put(g, debug_point(p.x, p.y), DEBUG_COLOR_GRID);
			p.x++;
		}
		p.y += DEBUG_CELL;
	}
}

static void	draw_debug_map(t_game *g)
{
	t_point	max;
	int		y;

	y = 0;
	while (y < g->map.height)
	{
		debug_draw_row(g, y);
		y++;
	}
	max.x = DEBUG_OFF_X + g->map.width * DEBUG_CELL;
	max.y = DEBUG_OFF_Y + g->map.height * DEBUG_CELL;
	debug_draw_grid_v(g, max);
	debug_draw_grid_h(g, max);
}

static int	cast_debug_ray(t_game *g, int col, t_raycasting *ray)
{
	t_raycasting	saved;

	if (!g || !ray)
		return (0);
	saved = g->ray;
	ray_init(g, col);
	ray_init_steps(g);
	if (!raycast_dda(g))
		return (g->ray = saved, 0);
	ray_perp_wall_distance(g);
	ray_draw_range(g);
	*ray = g->ray;
	g->ray = saved;
	return (1);
}


static t_point	debug_hit_point(t_game *g, t_raycasting ray)
{
	double	hit_x;
	double	hit_y;

	hit_x = g->player.pos.tile_pos.x + ray.perp_wall_dist * ray.ray_dir_x;
	hit_y = g->player.pos.tile_pos.y + ray.perp_wall_dist * ray.ray_dir_y;
	return (debug_world_to_screen(hit_x, hit_y));
}

static void	debug_draw_ray(t_game *g, t_point start, t_raycasting ray)
{
	t_point	end;

	end = debug_hit_point(g, ray);
	debug_line(g, start, end, DEBUG_COLOR_RAY);
	debug_fill(g, debug_point(end.x - 1, end.y - 1), 3, DEBUG_COLOR_HIT);
}

void	render_raycast_debug(t_game *g)
{
	t_raycasting	ray;
	t_point			start;
	int				col;

	if (!g)
		return ;
	draw_debug_map(g);
	// start = debug_player_point(g);
	start = debug_world_to_screen(g->player.pos.tile_pos.x,
			g->player.pos.tile_pos.y);
	col = 0;
	while (col < g->win.width)
	{
		if (cast_debug_ray(g, col, &ray))
			debug_draw_ray(g, start, ray);
		col += DEBUG_RAY_STEP;
	}
	debug_fill(g, debug_point(start.x - 2, start.y - 2), 5, DEBUG_COLOR_PLAYER);
}
