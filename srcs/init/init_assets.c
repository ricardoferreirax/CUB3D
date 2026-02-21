/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:18:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 21:48:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"

void	init_assets(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g);
	texture_load_walls(g);
	texture_load_floor_ceiling(g);
	texture_load_sprites(g);
}
