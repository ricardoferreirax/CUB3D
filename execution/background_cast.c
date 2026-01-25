/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:25:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/25 13:58:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

/* static void	background_calc_horizon(t_game *g, t_backcast *b, int y)
{
	int		mid;
	double	p;

	mid = g->win.height / 2;
	b->cam_z = 0.5 * (double)g->win.height;
	if (y > mid)
	{
		b->is_floor = 1;
		p = (double)(y - mid);
	}
	else
	{
		b->is_floor = 0;
		p = (double)(mid - y);
	}
	if (p < 1.0)
		p = 1.0;
	b->p = p;
}

static void	background_draw_row(t_game *g, t_backcast *b, int y)
{
	int	x;
	int	tx;
	int	ty;
	int	color;

	x = 0;
	while (x < g->win.width)
	{
		tx = (int)b->world_x;
		ty = (int)b->world_y;
		color = checker_color(tx, ty, b->is_floor);
		put_pixel(&g->win.frame_buffer, x, y, color);
		b->world_x += b->step_x;
		b->world_y += b->step_y;
		x++;
	}
}

static void	background_init_row(t_game *g, t_backcast *b, int y)
{
	background_calc_horizon(g, b, y);
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

	if (!g)
		return ;
	y = 0;
	while (y < g->win.height)
	{
		background_init_row(g, &b, y);
		background_draw_row(g, &b, y);
		y++;
	}
} */

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	*buf;
	int	stride;

	if (!img || !img->img_addr)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	buf = (int *)img->img_addr;
	stride = img->l_len / 4;
	buf[y * stride + x] = color;
}

static void	fill_row_fast(t_image *img, int y, int color)
{
	int	x;
	int	*buf;
	int	stride;

	buf = (int *)img->img_addr;
	stride = img->l_len / 4;
	x = 0;
	while (x < img->width)
	{
		buf[y * stride + x] = color;
		x++;
	}
}

void	render_background(t_game *g)
{
	int	y;
	int	mid;

	if (!g)
		return ;
	y = 0;
	mid = g->win.frame_buffer.height / 2;
	while (y < g->win.frame_buffer.height)
	{
		if (y < mid)
			fill_row_fast(&g->win.frame_buffer, y, 0x00111111);
		else
			fill_row_fast(&g->win.frame_buffer, y, 0x00333333);
		y++;
	}
}