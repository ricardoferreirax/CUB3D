/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:18:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/25 16:11:27 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

void	init_assets(t_game *game)
{
	if (!game || !game->mlx_ptr)
		exit_game(EXIT_MLX, game);
	texture_load_walls(game);
	texture_load_floor_ceiling(game);
	texture_load_sprites(game);
	init_gates(game);
	init_pacdots(game);
	init_energizers(game);
	init_ghosts(game);
	init_spritesheet(game);
	init_base(game);
}
