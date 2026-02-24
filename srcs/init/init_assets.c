/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:18:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 21:36:19 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

void	init_assets(t_game *game)
{
	if (!game || !game->mlx_ptr)
		exit_game(EXIT_MLX, game);
	texture_load_cube(game);
	texture_load_sprites(game);
	if (game->mode == MODE_PACMAN)
	{
		init_sprites(game);
		init_ghosts(game);
	}
}
