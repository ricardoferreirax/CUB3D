/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:41:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:04:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

char	map_tile(t_game *g, int y, int x)
{
	if (!g || !g->map.grid)
		return (VOID);
	if (y < 0 || x < 0 || y >= g->map.height || x >= g->map.width)
		return (VOID);
	return (g->map.grid[y][x]);
}
