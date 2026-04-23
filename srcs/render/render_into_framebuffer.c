/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_into_framebuffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:06:33 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:50:04 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"
#include "../ghosts/ghosts.h"

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
				ft_pixel_put(&s->win.frame_buffer, x + X_POS, y
					+ Y_POS, color);
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
					+ sprite->coord.x, point.y + sprite->coord.y);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&game->win.frame_buffer, point.x + coord.x, point.y
					+ coord.y, color);
			point.x++;
		}
		point.y++;
	}
}


void render_normal_ghost(t_game *game, t_point coord, t_ghost *ghost)
{
		if (ghost->invalid_dir == 0)
			render_sprite_into_framebuffer(game, coord,
				&ghost->frames.down[((ghost->pos.pixel_pos.x
						+ ghost->pos.pixel_pos.y) % 2)]);
		if (ghost->invalid_dir == 1)
			render_sprite_into_framebuffer(game, coord,
				&ghost->frames.right[((ghost->pos.pixel_pos.x
						+ ghost->pos.pixel_pos.y) % 2)]);
		if (ghost->invalid_dir == 2)
			render_sprite_into_framebuffer(game, coord,
				&ghost->frames.up[((ghost->pos.pixel_pos.x
						+ ghost->pos.pixel_pos.y) % 2)]);
		if (ghost->invalid_dir == 3)
			render_sprite_into_framebuffer(game, coord,
				&ghost->frames.left[((ghost->pos.pixel_pos.x
						+ ghost->pos.pixel_pos.y) % 2)]);
}

void render_eaten_ghost(t_game *game, t_point coord, t_ghost *ghost)
{
		if (ghost->invalid_dir == 0)
			render_sprite_into_framebuffer(game, coord, &ghost->frames.down[2]);
		if (ghost->invalid_dir == 1)
			render_sprite_into_framebuffer(game, coord, &ghost->frames.right[2]);
		if (ghost->invalid_dir == 2)
			render_sprite_into_framebuffer(game, coord, &ghost->frames.up[2]);
		if (ghost->invalid_dir == 3)
			render_sprite_into_framebuffer(game, coord, &ghost->frames.left[2]);
}

void	render_ghost_into_framebuffer(t_game *game, t_point coord,
		t_ghost *ghost)
{
	if (ghost->state == FRIGHTENED)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.scared[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	else
	{
		if(ghost->state != EATEN)
			render_normal_ghost(game, coord, ghost);
		else
			render_eaten_ghost(game, coord, ghost);

	}
}

void	render_ghosts_into_framebuffer(t_game *game)
{
	int		i;
	t_point	coord;

	i = -1;
	while (++i < 4)
	{
		if(ghost_ai(game, &game->ghosts[i], i))
			continue;
		coord.x = (game->ghosts[i].pos.pixel_pos.x - TILE_SIZE + X_POS);
		coord.y = (game->ghosts[i].pos.pixel_pos.y - TILE_SIZE + Y_POS);
		render_ghost_into_framebuffer(game, coord, &game->ghosts[i]);
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

void	render_pacdots_into_framebuffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->pacdot_count)
	{
		if (game->pacdots[i].active)
			render_sprite_into_framebuffer(game,
				(t_point){.y = game->pacdots[i].pos.pixel_pos.y
				+ Y_POS, .x = game->pacdots[i].pos.pixel_pos.x
				+ X_POS}, &game->sprite_sheet.sprites[37]);
		i++;
	}
}

void	render_energizers_into_framebuffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->energizer_count)
	{
		if (game->energizers[i].active)
			render_sprite_into_framebuffer(game,
				(t_point){.y = game->energizers[i].pos.pixel_pos.y
				+ Y_POS, .x = game->energizers[i].pos.pixel_pos.x
				+ X_POS}, &game->sprite_sheet.sprites[81]);
		i++;
	}
}


void	render_into_framebuffer(t_game *game)
{
	render_base_into_framebuffer(game);
	render_pacdots_into_framebuffer(game);
	render_energizers_into_framebuffer(game);
	render_ghosts_into_framebuffer(game);
	render_player_into_framebuffer(game);
	if(game->debug_mode)
		render_debug_symbols(game);
}
