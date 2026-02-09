/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:23:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/09 13:02:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	draw_rect(t_image *img, int x0, int y0, int w, int h, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel_fast(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_game *g, int map_y, int map_x, int px, int py)
{
	char	t;

	t = map_tile(g, map_y, map_x);
	if (t == WALL)
		draw_rect(&g->win.frame_buffer, px, py, MINI_TILE, MINI_TILE, C_WALL);
	else
		draw_rect(&g->win.frame_buffer, px, py, MINI_TILE, MINI_TILE, C_BG);
	if (t == PACDOT)
		draw_rect(&g->win.frame_buffer, px + MINI_TILE / 2, py + MINI_TILE / 2, 1, 1, C_DOT);
	if (t == ENERGIZER)
		draw_rect(&g->win.frame_buffer, px + MINI_TILE / 2 - 1, py + MINI_TILE / 2 - 1, 3, 3, C_ENERGIZER);
	if (t == WRAP_PORTS)
		draw_rect(&g->win.frame_buffer, px + 1, py + 1, MINI_TILE - 2, MINI_TILE - 2, C_PORT);
}

static void	draw_player_marker(t_game *g, int origin_x, int origin_y)
{
	int	px;
	int	py;

	px = origin_x + (int)(g->player.pos_x * MINI_TILE);
	py = origin_y + (int)(g->player.pos_y * MINI_TILE);
	draw_rect(&g->win.frame_buffer, px + MINI_TILE / 2 - 1, py + MINI_TILE / 2 - 1, 3, 3, C_PLAYER);
	draw_rect(&g->win.frame_buffer, px + MINI_TILE / 2 + (int)(g->player.dir_x * 2), py + MINI_TILE / 2 + (int)(g->player.dir_y * 2), 1, 1, C_PLAYER);
}

void	render_minimap_test(t_game *g)
{
	int	origin_x;
	int	origin_y;
	int	y;
	int	x;

	if (!g || !g->map.grid)
		return ;
	origin_x = MINI_MARGIN;
	origin_y = g->win.height - MINI_MARGIN - (g->map.height * MINI_TILE);
	if (origin_y < 0)
		return ;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			draw_tile(g, y, x,
				origin_x + x * MINI_TILE,
				origin_y + y * MINI_TILE);
			x++;
		}
		y++;
	}
	draw_player_marker(g, origin_x, origin_y);
}
