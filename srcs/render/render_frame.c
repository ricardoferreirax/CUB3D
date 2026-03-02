/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:32:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	clear_sprite_z(t_game *g)
{
	int		i;
	int		n;

	if (!g || !g->ray.sprite_z)
		return ;
	n = g->win.width * g->win.height;
	i = 0;
	while (i < n)
	{
		g->ray.sprite_z[i] = 1e30;
		i++;
	}
}

static void	apply_input(t_game *g)
{
	if (!g)
		return ;
	player_rotation_controller(g);
	player_movement_controller(g);
}

void	render_base_into_buffer(t_game *s)
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
				ft_pixel_put(&s->win.frame_buffer, x + s->win.width / 2, y + s->win.height / 2, color);
			x++;
		}
		y++;
	}
}

void render_sprite_into_framebuffer(t_game *game, t_point coord, t_sprite_ref *sprite)
{
	t_point point;
	unsigned int color;
	point.y = 0;
	while(point.y < sprite->height)
	{
		point.x = 0;
		while(point.x < sprite->width)
		{
			color = pixel_get(&game->sprite_sheet.sprite_img, point.x + sprite->coord.x, point.y + sprite->coord.y);
			if((color >> 24) != 0xFF)
				ft_pixel_put(&game->win.frame_buffer, point.x + coord.x, point.y, color);
			point.x++;
		}
		point.y++;
	}
}

void render_ghosts_into_framebuffer(t_game *game)
{
	int i = -1;
	while(++i < 4)
		render_sprite_into_framebuffer(game, game->ghosts[i].pos.pixel_pos, game->ghosts[i].frames.left);
}

void render_into_framebuffer(t_game *game)
{
	render_base_into_buffer(game);
	render_ghosts_into_framebuffer(game);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game);
	apply_input(game);
	render_ceiling_texture(game);
	render_floor_texture(game);
	process_raycasting(game);
	handle_gate_toggle(game);
	clear_sprite_z(game);
	render_all_sprites(game);
	render_minimap_test(game);
	render_into_framebuffer(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr, game->win.frame_buffer.img_ptr, 0, 0);
}
