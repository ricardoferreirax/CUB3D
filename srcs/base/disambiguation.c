/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disambiguation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:51:17 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:56:19 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int	disambiguation(t_point player_spawn, t_map map, t_point coord)
{
	unsigned char	mask;
	int				final;

	flood_fill(map.grid, player_spawn.x, player_spawn.y);
	mask = mask_constructor(&map, &coord, 'F');
	final = find_disamb_sprite(mask);
	return (final);
}
