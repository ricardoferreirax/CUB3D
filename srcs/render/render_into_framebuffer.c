/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_into_framebuffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:06:33 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:52:59 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"

void	render_base_into_framebuffer(t_game *s)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < s->base.height)
	{
		x = 0;
		while (x < s->base.width)
		{
			color = pixel_get(&s->base, x, y);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&s->win.frame_buffer, (x + X_POS) % s->win.width,
					(y + Y_POS) % s->win.height, color);
			x++;
		}
		y++;
	}
}

void	render_sprite_into_framebuffer(t_game *game, t_point coord,
		t_sprite_ref *sprite)
{
	t_point			point;
	unsigned int	color;

	point.y = 0;
	while (point.y < sprite->height)
	{
		point.x = 0;
		while (point.x < sprite->width)
		{
			color = pixel_get(&game->sprite_sheet.sprite_img, point.x
					+ sprite->coord.x % game->win.frame_buffer.width, point.y + sprite->coord.y);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&game->win.frame_buffer, (point.x + coord.x)
					% game->win.frame_buffer.width, (point.y + coord.y)
					% game->win.frame_buffer.height, color);
			point.x++;
		}
		point.y++;
	}
}

void	render_player(t_game *game, t_point coord)
{
	if ((game->player.target_dir.y) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.down[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.right[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.y) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.up[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.left[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
}

void	render_player_into_framebuffer(t_game *game)
{
	t_point	coord;

	coord.x = (((game->player.pos.tile_pos.x - 0.5) * TILE_SIZE) + X_POS) - 3;
	coord.y = (((game->player.pos.tile_pos.y - 0.5) * TILE_SIZE) + Y_POS) - 3;
	game->player.pos.pixel_pos.x = coord.x;
	game->player.pos.pixel_pos.y = coord.y;
	render_player(game, coord);
}

void	render_into_framebuffer(t_game *game)
{
	render_base_into_framebuffer(game);
	render_pacdots_into_framebuffer(game);
	render_energizers_into_framebuffer(game);
	render_ghosts_into_framebuffer(game);
	render_player_into_framebuffer(game);
	if (game->debug_mode)
		render_debug_symbols(game);
}
