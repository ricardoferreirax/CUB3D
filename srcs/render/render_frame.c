/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/07 22:07:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	clear_sprite_z(t_game *g)
{
	int	i;
	int	n;

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
				ft_pixel_put(&s->win.frame_buffer, x + 50,
					y + s->win.height - s->base.height - 100, color);
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

t_point	continue_travel(t_point *ghost_pos, int invalid_dir)
{
	int	dir;

	dir = (invalid_dir + 2) % 4;
	int direction[4][2] = {
		{0, -1}, // up
		{-1, 0}, // left
		{0, 1},  // down
		{1, 0}   // right
	};
	return ((t_point){.x = ghost_pos->x + direction[dir][0], .y = ghost_pos->y
		+ direction[dir][1]});
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

int	chose_next_move(t_ghost *ghost, char **map)
{
	int	i;
	int	best;
	int	best_dir;
	int	dist;

	int direction[4][2] = {
		{-1, 0}, // 0 = up
		{0, -1}, // 1 = left
		{1, 0},  // 2 = down
		{0, 1}   // 3 = right
	};
	i = 0;
	best = -1;
	best_dir = -1;
	if(!map)
		return -1;
	while (i < 4)
	{
		if ((map[ghost->pos.pixel_pos.y / 8 + direction[i][0]][ghost->pos.pixel_pos.x / 8 + direction[i][1]] != '1' ) && i != ghost->invalid_dir)
		{
			dist = distance_to_target(ghost, direction[i][0], direction[i][1]);
			if (best == -1 || dist < best)
			{
				best = dist;
				best_dir = i;
			}
		}
		i++;
	}
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	ghost->pos.pixel_pos.y += direction[best_dir][0];
	ghost->pos.pixel_pos.x += direction[best_dir][1];
	return ((best_dir + 2) % 4);
}

int	update_ghost(t_ghost *ghost)
{
	if (ghost->pos.pixel_pos.x % 8 != 0 && ghost->pos.pixel_pos.y % 8 != 0)
	{
		ghost->pos.pixel_pos = continue_travel(&ghost->pos.pixel_pos,
				ghost->invalid_dir);
		return 0;
	}
	ghost->invalid_dir = chose_next_move(ghost, ghost->mental_map);
	if(ghost->invalid_dir == -1)
		return -1;
	return 0;
}

void	render_ghosts_into_framebuffer(t_game *game)
{
	int		i;
	t_point	coord;

	i = -1;
	while (++i < 4)
	{
		if(game->ghosts[i].name == DISABLED)
			continue;
		update_ghost(&game->ghosts[i]);
		coord.x = (game->ghosts[i].pos.pixel_pos.x * 8 + game->win.width / 2);
		coord.y = (game->ghosts[i].pos.pixel_pos.y * 8 + game->win.height / 2);
		render_sprite_into_framebuffer(game, coord,
			&game->ghosts[i].frames.left[0]);
	}
}

void	render_into_framebuffer(t_game *game)
{
	render_base_into_buffer(game);
	render_ghosts_into_framebuffer(game);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game, NULL);
	player_controller(game);
	render_ceiling_texture(game);
	render_floor_texture(game);
	raycast_frame(game);
	handle_gate_toggle(game);
	clear_sprite_z(game);
	render_all_sprites(game);
	render_into_framebuffer(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
		game->win.frame_buffer.img_ptr, 0, 0);
}
