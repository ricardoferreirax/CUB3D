/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:18:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/13 22:58:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	init_assets(t_game *g)
{
	if (!g) return;
	if (!g->mlx_ptr) exit_game(EXIT_MLX, g);
	texture_load_xpm(g, &g->pac.tex, "./textures/pacdot.xpm");
	if (!g->pac.tex.img_addr) exit_game(EXIT_MLX, g);
}


