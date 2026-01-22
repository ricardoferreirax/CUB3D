/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:25:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/22 15:15:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static void	calc_background_horizon(t_game *g, t_backcast *b, int y)
{
	int		mid;
	double	p;

	mid = g->win.height / 2;
	if (y > mid)
	{
		b->is_floor = 1;
		b->cam_z = 0.5 * (double)g->win.height;
		p = (double)(y - mid);
	}
	else
	{
		b->is_floor = 0;
		b->cam_z = 0.5 * (double)g->win.height;
		p = (double)(mid - y);
	}
	if (p < 1.0)
		p = 1.0;
	b->p = p;
}

void	background_init_row(t_game *g, t_backcast *b, int y)
{
	calc_background_horizon(g, b, y);
	b->ray0_x = g->player.dir_x - g->player.plane_x;
	b->ray0_y = g->player.dir_y - g->player.plane_y;
	b->ray1_x = g->player.dir_x + g->player.plane_x;
	b->ray1_y = g->player.dir_y + g->player.plane_y;
	b->row_dist = b->cam_z / b->p;
	b->step_x = b->row_dist * (b->ray1_x - b->ray0_x) / (double)g->win.width;
	b->step_y = b->row_dist * (b->ray1_y - b->ray0_y) / (double)g->win.width;
	b->world_x = g->player.pos_x + b->row_dist * b->ray0_x;
	b->world_y = g->player.pos_y + b->row_dist * b->ray0_y;
}

void	render_background(t_game *g)
{
	t_backcast	b;
	int			y;
	int			x;
	int			tx;
	int			ty;
	int			color;

	y = 0;
	while (y < g->win.height)
	{
		background_init_row(g, &b, y);
		x = 0;
		while (x < g->win.width)
		{
			tx = (int)b.world_x;
			ty = (int)b.world_y;
			if (b.is_floor)
			{
				if (((tx + ty) & 1) == 0)
					color = 0x00303030;
				else
					color = 0x00404040;
			}
			else
			{
				if (((tx + ty) & 1) == 0)
					color = 0x00101010;
				else
					color = 0x00181818;
			}
			put_pixel(&g->win.frame_buffer, x, y, color);
			b.world_x += b.step_x;
			b.world_y += b.step_y;
			x++;
		}
		y++;
	}
}
