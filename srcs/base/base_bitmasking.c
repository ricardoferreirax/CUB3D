/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_bitmasking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:15:31 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:18:02 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static const uint16_t	g_bitmask_to_tile[256] = {
	[0xFF] = 39,  // Filled Tile
	[0x31] = 16,  // 0011 0001 Top Left
	[0x62] = 18,  // 0110 0010 Top Right
	[0x98] = 60,  // 1001 1000 Bottom Left
	[0xC4] = 62,  // 1100 0100 Bottom Right
	[0xFD] = 127, // T Bottom Left
	[0xFE] = 128, // T Bottom Right
	[0xF7] = 106, // T Top Right
	[0xFB] = 105, // T Top Left
	[0xB9] = 38,  // Vertical Left
	[0xBB] = 38,
	[0xBD] = 38,
	[0xBF] = 38,
	[0xE6] = 40, // Vertical Right
	[0xEE] = 40,
	[0xE7] = 40,
	[0xEF] = 40,
	[0x73] = 17, // Horizontal Top
	[0x77] = 17,
	[0x7B] = 17,
	[0x7F] = 17,
	[0xDC] = 61, // Horizontal Bottom
	[0xDE] = 61,
	[0xDD] = 61,
	[0xDF] = 61,
	// Borders
	[0xB1] = 104, // Bottom Vertical Left, Double Wall
	[0xB8] = 126, // Top Vertical Left, Double Wall
	[0xE4] = 129, // Top Vertical Roght, Double Wall
	[0xE2] = 107, // Bottom Vertical Right, Double Wall
	[0x71] = 83,  // Top Horizontal Right, Double Wall
	[0x72] = 84,  // Top Horizontal Left, Double Wall
	[0xD8] = 150, // Bottom Horizontal Right, Double Wall
	[0xD4] = 151, // Bottom Horizontal Left, Doublw Wall
	// [0x90] = 148, // Bottom Left Curve
	// [0x30] = 82, // Bottom Right Curve
	// [0x60] = 85, // Top Right Curve
	// [0xC0] = 149, // Bottom Right Curve
	// [0x10] = 103, // Right Doorframe
	// [0x40] = 101, // Left Doorframe
};

static const uint16_t	g_bitmask_totile[256] = {
	[0xFF] = 39,
	[0x04] = 149, // Bottom Right Curve
	[0x08] = 148, // Bottom Left Curve
	[0x02] = 85,  // Top Right Curve
	[0x01] = 82,  // top left curve
	[0xCE] = 16,  // Top LEft corner
	[0x67] = 60,  // Bottom Left corner
	[0x3B] = 62,  // Bottom Right Corner
	[0x9D] = 18,  // Top roght corner
	[0x46] = 41,  // Vertical Wall RIght
	[0x44] = 41,  [0x42] = 41, [0x40] = 41,
	[0x19] = 43, // vertical Wall left
	[0x18] = 43,  [0x11] = 43, [0x10] = 43,
	[0x8C] = 20, // Bottom Wall
	[0x88] = 20,  [0x84] = 20, [0x80] = 20,
	[0x23] = 64, // Top Wall
	[0x22] = 64,  [0x21] = 64, [0x20] = 64,
	[0xCC] = 103, // Right Door Frame
	[0x9C] = 101, // LEft Door Frame
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

	tile = g_bitmask_totile[mask];
	if (tile == 0)
		return (0);
	return (tile);
}

int	squared_corners(int final)
{
	if (final == 148)
		return (63);
	if (final == 82)
		return (19);
	if (final == 85)
		return (21);
	if (final == 149)
		return (65);
	return (final);
}

t_point	player_spawn(char **map)
{
	t_point	pos;
	char	*str;
	int		i;

	str = "NEWS";
	i = 0;
	while (str[i])
	{
		pos = find_c(map, str[i]);
		if (pos.x >= 0 && pos.y >= 0)
			break ;
		i++;
	}
	return (pos);
}
