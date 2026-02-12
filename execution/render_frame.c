/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 22:21:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	apply_input(t_game *g)
{
	if (!g)
		return ;
	player_rotation_controller(g);
	movement_controller(g);
}

static void	fill_row_fast(t_image *img, int y, int color)
{
	unsigned int	*row;
	int				stride;
	int				x;

	stride = img->l_len / 4;
	row = (unsigned int *)img->img_addr + (y * stride);
	x = 0;
	while (x < img->width)
		row[x++] = (unsigned int)color;
}

void	fill_ceiling_color(t_image *img, int color, int horizon)
{
	int	y;
	int	end;

	if (!img || !img->img_addr)
		return ;
	end = img->height / 2 - horizon;
	if (end < 0) end = 0;
	if (end > img->height) end = img->height;
	y = 0;
	while (y < end)
		fill_row_fast(img, y++, color);
}

void	fill_floor_color(t_image *img, int color, int horizon)
{
	int	y;
	int	start;

	if (!img || !img->img_addr)
		return ;
	start = img->height / 2 - horizon;
	if (start < 0) start = 0;
	if (start > img->height) start = img->height;
	y = start;
	while (y < img->height)
		fill_row_fast(img, y++, color);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game);
	apply_input(game);
	render_ceiling(game);
	render_floor(game);
	process_raycasting(game);
	render_minimap_test(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr, game->win.frame_buffer.img_ptr, 0, 0);
}

