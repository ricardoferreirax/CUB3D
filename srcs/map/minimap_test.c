/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:23:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 23:14:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	mini_rect(t_image *img, int x0, int y0, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_fast(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

static int	minimap_origin(t_game *g, int *ox, int *oy)
{
	if (!g || !g->map.grid || !ox || !oy)
		return (0);
	*ox = MINI_MARGIN;
	*oy = g->win.height - MINI_MARGIN - (g->map.height * MINI_TILE);
	if (*oy < 0)
		return (0);
	return (1);
}

static void	minimap_draw_grid(t_game *g, int ox, int oy)
{
	int		my;
	int		mx;
	char	t;
	int		px;
	int		py;

	my = 0;
	while (my < g->map.height)
	{
		mx = 0;
		while (mx < g->map.width)
		{
			t = map_get_tile(g, my, mx);
			px = ox + mx * MINI_TILE;
			py = oy + my * MINI_TILE;
			if (t == VOID)
				mini_rect(&g->win.frame_buffer, px, py, MINI_TILE, C_BG);
			else if (t == WALL)
				mini_rect(&g->win.frame_buffer, px, py, MINI_TILE, C_WALL);
			else if (t == WRAP_PORTS)
				mini_rect(&g->win.frame_buffer, px, py, MINI_TILE, C_PORT);
			else
				mini_rect(&g->win.frame_buffer, px, py, MINI_TILE, C_BG);
			if (t == PACDOT)
				put_pixel_fast(&g->win.frame_buffer,
					px + MINI_TILE / 2, py + MINI_TILE / 2, C_DOT);
			else if (t == ENERGIZER)
				mini_rect(&g->win.frame_buffer,
					px + MINI_TILE / 2 - 1, py + MINI_TILE / 2 - 1, 3, C_ENERGIZER);
			else if (t == GATE)
				mini_rect(&g->win.frame_buffer,
					px + MINI_TILE / 2 - 1, py + MINI_TILE / 2 - 1, 3, 0x00FF00FF);
			mx++;
		}
		my++;
	}
}

static void	minimap_draw_player(t_game *g, int ox, int oy)
{
	int	px;
	int	py;
	int	cx;
	int	cy;

	px = ox + (int)(g->player.pos_x * MINI_TILE);
	py = oy + (int)(g->player.pos_y * MINI_TILE);
	cx = px + MINI_TILE / 2;
	cy = py + MINI_TILE / 2;
	mini_rect(&g->win.frame_buffer, cx - 1, cy - 1, 3, C_PLAYER);
	put_pixel_fast(&g->win.frame_buffer, cx + (int)(g->player.dir_x * 2.0),
		cy + (int)(g->player.dir_y * 2.0), C_PLAYER);
}

void	render_minimap_test(t_game *g)
{
	int	ox;
	int	oy;

	if (!minimap_origin(g, &ox, &oy))
		return ;
	minimap_draw_grid(g, ox, oy);
	minimap_draw_player(g, ox, oy);
}
