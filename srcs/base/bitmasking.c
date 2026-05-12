/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmasking.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:15:31 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/12 11:26:37 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static const uint16_t		g_bitmask_to_tile[256] = {
[0xFF] = 39,
[0x31] = 16,
[0x62] = 18,
[0x98] = 60,
[0xC4] = 62,
[0xFD] = 127,
[0xFE] = 128,
[0xF7] = 106,
[0xFB] = 105,
[0xB9] = 38,
[0xBB] = 38,
[0xBD] = 38,
[0xBF] = 38,
[0xE6] = 40,
[0xEE] = 40,
[0xE7] = 40,
[0xEF] = 40,
[0x73] = 17,
[0x77] = 17,
[0x7B] = 17,
[0x7F] = 17,
[0xDC] = 61,
[0xDE] = 61,
[0xDD] = 61,
[0xDF] = 61,
[0xB1] = 104,
[0xB8] = 126,
[0xE4] = 129,
[0xE2] = 107,
[0x71] = 83,
[0x72] = 84,
[0xD8] = 150,
[0xD4] = 151,
};

static const uint16_t		g_disamb_bitmask_to_tile[256] = {
[0xff] = 39,
[0x04] = 149,
[0x08] = 148,
[0x02] = 85,
[0x01] = 82,
[0xce] = 16,
[0x67] = 60,
[0x3b] = 62,
[0x9d] = 18,
[0x46] = 41,
[0x44] = 41,
[0x41] = 41,
[0x40] = 41,
[0x19] = 43,
[0x18] = 43,
[0x11] = 43,
[0x10] = 43,
[0x8c] = 20,
[0x88] = 20,
[0x84] = 20,
[0x80] = 20,
[0x23] = 64,
[0x22] = 64,
[0x21] = 64,
[0x20] = 64,
[0xcc] = 103,
[0x9c] = 101,
};

static const unsigned char	g_bits[8] = {
	(1 << 7),
	(1 << 5),
	(1 << 6),
	(1 << 4),
	(1 << 2),
	(1 << 3),
	(1 << 1),
	(1 << 0)
};

static const t_point		g_neighborghs[8] = {
	(t_point){.y = -1, .x = 0},
	(t_point){.y = 1, .x = 0},
	(t_point){.y = 0, .x = -1},
	(t_point){.y = 0, .x = 1},
	(t_point){.y = -1, .x = -1},
	(t_point){.y = -1, .x = 1},
	(t_point){.y = 1, .x = -1},
	(t_point){.y = 1, .x = 1}
};

int	find_sprite(unsigned int mask)
{
	uint16_t	tile;

	tile = g_bitmask_to_tile[mask];
	if (tile == 0)
		return (0);
	return (tile);
}

int	find_disamb_sprite(unsigned int mask)
{
	uint16_t	tile;

	tile = g_disamb_bitmask_to_tile[mask];
	if (tile == 0)
		return (0);
	return (tile);
}

bool	is_wall(t_map *map, t_point coord, int neighborgh, char c)
{
	coord.x = coord.x + g_neighborghs[neighborgh].x;
	coord.y = coord.y + g_neighborghs[neighborgh].y;
	if (coord.x < 0 || coord.y < 0)
		return (false);
	if (coord.x >= map->width || coord.y >= map->height)
		return (false);
	return (map->grid[coord.y][coord.x] == c);
}

unsigned char	mask_constructor(t_map *map, t_point *coord, char c)
{
	unsigned char	mask;
	int				i;

	mask = 0;
	i = 0;
	while (i < 8)
	{
		if (is_wall(map, *coord, i, c))
			mask |= g_bits[i];
		i++;
	}
	return (mask);
}
