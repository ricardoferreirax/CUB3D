/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/21 21:08:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

void	init_null(t_game *game)
{
	int	i;
	int	j;

	game->win.win_ptr = NULL;
	game->win.frame_buffer.img_ptr = NULL;
	game->win.frame_buffer.img_addr = NULL;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (j++ < 4)
		{
		}
	}
}

void	init_window(t_game *game)
{
	game->win.ntilesx = xtile(game->map.grid);
	game->win.ntilesy = ytile(game->map.grid);
	game->win.width = TILE_SIZE * game->win.ntilesx;
	game->win.height = TILE_SIZE * game->win.ntilesy;
	game->win.win_ptr = mlx_new_window(game->mlx_ptr, game->win.width,
			game->win.height, "Pac-Man");
	game->win.frame_buffer.img_ptr = mlx_new_image(game->mlx_ptr,
			game->win.width, game->win.height);
	game->win.frame_buffer.img_addr = mlx_get_data_addr(game->win.frame_buffer.img_ptr,
			&game->win.frame_buffer.bpp, &game->win.frame_buffer.l_len,
			&game->win.frame_buffer.endian);
	game->win.frame_buffer.width = game->win.width;
	game->win.frame_buffer.height = game->win.height;
}

void	init_ghost(t_game *game, t_ghost *ghost)
{
	ghost->is_steping_on_pacdot = 0;
	ghost->mental_map = copy_map(game->map.grid);
	ghost->state = SCATTER;
	if (ghost->name == BLINKY)
		init_blinky(game, ghost);
	if (ghost->name == PINKY)
		init_pinky(game, ghost);
	if (ghost->name == INKY)
		init_inky(game, ghost);
	if (ghost->name == CLYDE)
		init_clyde(game, ghost);
}

void	init_ghosts(t_game *game)
{
	int	i;

	game->ghost = malloc(sizeof(t_ghost) * 4);
	i = -1;
	while (++i < 4)
		init_ghost(game, &game->ghost[i]);
}

int uselesstile(t_point point)
{
	if(point.y == 55)
	{
		if(point.x == 154 || point.x == 163)
			return 1;
	}
	return 0;
}

int	init_spritesheet(t_game *game)
{
	t_point	control;
	int		i;

	game->sprite_sheet.sprites = malloc(sizeof(t_sprite_ref) * 256);
	i = 0;
	control.y = 1;
	while (control.y <= 74)
	{
		control.x = 1;
		while (control.x < 373)
		{
			if(!uselesstile(control))
			{
				game->sprite_sheet.sprites[i].coord = control;
				game->sprite_sheet.sprites[i].width = 8;
				game->sprite_sheet.sprites[i].height = 8;
				i++;
			}
			control.x += 9;
		}
		control.y += 9;
	}
	control.y = 83;
	while(control.y <= 168)
	{
		control.x = 1;
		while(control.x < 574)
		{
			game->sprite_sheet.sprites[i].coord = control;
			game->sprite_sheet.sprites[i].width = 16;
			game->sprite_sheet.sprites[i].height = 16;
			control.x += 17;
		}
		control.y += 17;
	}
	return i;
}

void	init_game(t_game *game)
{
	// ft_bzero(game, sizeof(t_game));
	init_null(game);
	init_window(game);
	init_ghosts(game);
	init_spritesheet(game);
}
