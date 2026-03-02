/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:04:01 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/25 16:08:01 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "initializer.h"
int	find_sprite(unsigned int mask)
{
	static const uint16_t bitmask_to_tile[256] = {
		[0xFF] = 39, // Filled Tile
		[0x31] = 16, // 0011 0001 Top Left
		[0x62] = 18, // 0110 0010 Top Right
		[0x98] = 60, // 1001 1000 Bottom Left
		[0xC4] = 62, // 1100 0100 Bottom Right
		[0xFD] = 127, // T Bottom Left
		[0xFE] = 128, // T Bottom Right
		[0xF7] = 106, // T Top Right
		[0xFB] = 105, // T Top Left
		[0xB9] = 38, // Vertical Left
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
		[0x71] = 83, //Top Horizontal Right, Double Wall
		[0x72] = 84, //Top Horizontal Left, Double Wall
		[0xD8] = 150, //Bottom Horizontal Right, Double Wall
		[0xD4] = 151, //Bottom Horizontal Left, Doublw Wall
		// [0x90] = 148, // Bottom Left Curve
		// [0x30] = 82, // Bottom Right Curve
		// [0x60] = 85, // Top Right Curve
		// [0xC0] = 149, // Bottom Right Curve
		// [0x10] = 103, // Right Doorframe
		// [0x40] = 101, // Left Doorframe
	};
	uint16_t tile = bitmask_to_tile[mask];
	if(tile == 0)
		return 0;
	return tile;
}

int find_disamb_sprite(unsigned int mask)
{
	static const uint16_t bitmask_totile[256] = {
	[0xFF] = 39,
	[0x04] = 149, //Bottom Right Curve
	[0x08] = 148, //Bottom Left Curve
	[0x02] = 85, //Top Right Curve
	[0x01] = 82, //top left curve
	[0xCE] = 16, // Top LEft corner
	[0x67] = 60, //Bottom Left corner
	[0x3B] = 62, // Bottom Right Corner
	[0x9D] = 18, //Top roght corner
	[0x46] = 41, // Vertical Wall RIght
	[0x44] = 41,
	[0x42] = 41,
	[0x40] = 41,
	[0x19] = 43, //vertical Wall left
	[0x18] = 43,
	[0x11] = 43,
	[0x10] = 43,
	[0x8C] = 20, //Bottom Wall
	[0x88] = 20,
	[0x84] = 20,
	[0x80] = 20,
	[0x23] = 64, //Top Wall
	[0x22] = 64,
	[0x21] = 64,
	[0x20] = 64,
	[0xCC] = 103, //Right Door Frame
	[0x9C] = 101, //LEft Door Frame
	};
	uint16_t tile = bitmask_totile[mask];
	if(tile == 0)
		return 0;
	return tile;
}

void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || x >= xtile(map) || y < 0
		|| y >= ytile(map) || map[y][x] == 'F'
		|| map[y][x] == '1' || map[x][y] == 'D')
		return ;
	if(map[y][x] == 'G')
	{
		map[y][x] = 'F';
		return;
	}
    map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}



int disambiguation(char **map, t_point coord)
{
	flood_fill(map, 24, 14);
	unsigned char	mask;

	mask = 0;
	if (coord.y != 0 && map[coord.y - 1][coord.x] == 'F')
		mask |= (1 << 7);
	if (coord.y != ytile(map) - 1 && map[coord.y + 1][coord.x] == 'F')
		mask |= (1 << 5);
	if (coord.x != 0 && map[coord.y][coord.x - 1] == 'F')
		mask |= (1 << 6);
	if (coord.x != xtile(map) - 1 && map[coord.y][coord.x + 1] == 'F')
		mask |= (1 << 4);
	if (coord.y != 0)
	{
		if (coord.x != 0 && map[coord.y - 1][coord.x - 1] == 'F')
			mask |= (1 << 2);
		if (coord.x != xtile(map) - 1 && map[coord.y - 1][coord.x
			+ 1] == 'F')
			mask |= (1 << 3);
	}
	if (coord.y != ytile(map) - 1)
	{
		if (coord.x != 0 && map[coord.y + 1][coord.x - 1] == 'F')
			mask |= (1 << 1);
		if (coord.x != xtile(map) - 1 && map[coord.y + 1][coord.x
			+ 1] == 'F')
			mask |= (1 << 0);
	}
	int final = find_disamb_sprite(mask);
	return final;
}

int squared_corners(int final)
{
	if(final == 148)
		return(63);
	if(final == 82)
		return(19);
	if(final == 85)
		return(21);
	if(final == 149)
		return(65);
	return(final);
}

int	which_wall(t_map map, t_point *coord)
{
	unsigned char	mask;

	mask = 0;
	if (coord->y != 0 && map.grid[coord->y - 1][coord->x] == '1')
		mask |= (1 << 7);
	if (coord->y != map.height - 1 && map.grid[coord->y + 1][coord->x] == '1')
		mask |= (1 << 5);
	if (coord->x != 0 && map.grid[coord->y][coord->x - 1] == '1')
		mask |= (1 << 6);
	if (coord->x != map.width - 1 && map.grid[coord->y][coord->x + 1] == '1')
		mask |= (1 << 4);
	if (coord->y != 0)
	{
		if (coord->x != 0 && map.grid[coord->y - 1][coord->x - 1] == '1')
			mask |= (1 << 2);
		if (coord->x != map.width - 1 && map.grid[coord->y - 1][coord->x
			+ 1] == '1')
			mask |= (1 << 3);
	}
	if (coord->y != map.height - 1)
	{
		if (coord->x != 0 && map.grid[coord->y + 1][coord->x - 1] == '1')
			mask |= (1 << 1);
		if (coord->x != map.width - 1 && map.grid[coord->y + 1][coord->x
			+ 1] == '1')
			mask |= (1 << 0);
	}
	int final = find_sprite(mask);
	char **temp;
	temp = copy_map(map.grid);
	if(final == 0)
		final = disambiguation(temp, *coord);
	if(map.grid[coord->y][coord->x] == 'M')
		final = squared_corners(final);
	free_2d((void **)temp);
	return final;
}

int	which_tile(t_game *game, t_point coord)
{
	if (game->map.grid[coord.y][coord.x] == '1')
		return (which_wall(game->map, &coord));
	else
		return (170);
}

void	put_tile_inbase(t_game *g, int tile_code, unsigned int color,
		t_point point)
{
	int	ty;
	int	tx;

	ty = 0;
	while (ty < g->sprite_sheet.sprites[tile_code].height)
	{
		tx = 0;
		while (tx < g->sprite_sheet.sprites[tile_code].width)
		{
			color = pixel_get(&g->sprite_sheet.sprite_img,
					g->sprite_sheet.sprites[tile_code].coord.x + tx,
					g->sprite_sheet.sprites[tile_code].coord.y + ty);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&g->base, point.x * 8 + tx, point.y * 8 + ty,
					color);
			tx++;
		}
		ty++;
	}
}

void	init_base(t_game *s)
{
	int				tile;
	t_point			point;
	unsigned int	color;

	color = 0;
	point.x = 0;
	point.y = 0;
	ft_printf("HEKKI");
	s->base.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width, s->win.height);
	s->base.img_addr = mlx_get_data_addr(s->base.img_ptr, &s->base.bpp,
			&s->base.l_len, &s->base.endian);
	s->base.width = s->map.width * TILE_SIZE;
	s->base.height = s->map.height * TILE_SIZE;
	ft_printf("HEKKI");
	while (s->map.grid[point.y])
	{
		ft_printf("Hekki");
		point.x = 0;
		while (s->map.grid[point.y][point.x])
		{
			printf("ITERATION NUMBER: %d", point.x);
			tile = which_tile(s, point);
			put_tile_inbase(s, tile, color, point);
			point.x++;
		}
		point.y++;
	}
}
