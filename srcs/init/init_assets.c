/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:18:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/23 22:48:36 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"

void	init_assets(t_game *game)
{
	if (!game || !game->mlx_ptr)
		exit_game(EXIT_MLX, game);
	texture_load_walls(game);
	texture_load_floor_ceiling(game);
	texture_load_sprites(game);
	init_pacdots(game);
	init_energizers(game);
	init_ghosts(game);
}
