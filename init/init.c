/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/14 16:08:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

void init_null(t_game *game)
{
	game->win.win_ptr = NULL;
	game->win.frame_buffer.img_ptr = NULL;
	game->win.frame_buffer.img_addr = NULL;
	int i = -1;
	while(++i < 4)
	{
		int j = -1;
		while(j++ < 4)
		{
		}
	}
}

void	init_window(t_game *game)
{
	game->win.ntilesx = xtile(game->map.grid);
	game->win.ntilesy = ytile(game->map.grid);
	game->win.width = 8 * game->win.ntilesx;
	game->win.height = 8 * game->win.ntilesy;
	game->win.win_ptr = mlx_new_window(game->mlx_ptr, game->win.width, game->win.height, "Pac-Man");
	game->win.frame_buffer.img_ptr = mlx_new_image(game->mlx_ptr, game->win.width, game->win.height);
	game->win.frame_buffer.img_addr = mlx_get_data_addr(game->win.frame_buffer.img_ptr, &game->win.frame_buffer.bpp, &game->win.frame_buffer.l_len, &game->win.frame_buffer.endian);
	game->win.frame_buffer.width = game->win.width;
	game->win.frame_buffer.height = game->win.height;

}

void init_ghost(t_game *game, t_ghost *ghost)
{
	ghost->is_steping_on_pacdot = 0;
	ghost->mental_map = copy_map(game->map.grid);
	ghost->state = SCATTER;
	if(ghost->name == BLINKY)
		init_blinky(game, ghost);
	if(ghost->name == PINKY)
		init_pinky(game, ghost);
	if(ghost->name == INKY)
		init_inky(game, ghost);
	if(ghost->name == CLYDE)
		init_clyde(game, ghost);
}

void init_ghosts(t_game *game)
{
	game->ghost = malloc(sizeof(t_ghost) * 4);
	int i = -1;
	while (++i < 4)
		init_ghost(game, &game->ghost[i]);
}

void init_game(t_game *game)
{
	init_null(game);
	init_window(game);
	init_ghosts(game);
}
