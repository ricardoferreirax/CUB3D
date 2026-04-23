/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:05:27 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:18:02 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"


void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || x >= xtile(map) || y < 0
		|| y >= ytile(map) || map[y][x] == 'F'
		|| map[y][x] == '1' || map[y][x] == 'D')
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

int disambiguation(t_point player_spawn, char **map, t_point coord)
{
	flood_fill(map, player_spawn.x, player_spawn.y);
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

t_point player_spawn(char **map)
{
	t_point pos;
	char *str = "NEWS";
	int i = 0;
	while(str[i])
	{
		pos = find_c(map, str[i]);
		if(pos.x >= 0 && pos.y >= 0)
			break;
		i++;
	}
	return pos;
}

int	which_wall(char **original_map, t_map map, t_point *coord)
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
		final = disambiguation(player_spawn(original_map), temp, *coord);
	if(original_map[coord->y][coord->x] == 'M')
		final = squared_corners(final);
	free_2d((void **)temp);
	return final;
}

int	which_tile(char **original_map, t_map *map, t_point coord, bool debug)
{
	if (map->grid[coord.y][coord.x] == '1')
		return (which_wall(original_map, *map, &coord));
	else
	{
		if(debug)
			return(59);
		return (170);
	}
}

void	put_tile_inbase(t_game *g, int tile_code, unsigned int color,
		t_point point)
{
	int	ty;
	int	tx;
	t_point pallete;
	pallete.x = MAP_PALLETE_X;
	pallete.y = MAP_PALLETE_Y;
	ty = 0;
	while (ty < g->sprite_sheet.sprites[tile_code].height)
	{
		tx = 0;
		while (tx < g->sprite_sheet.sprites[tile_code].width)
		{
			color = pixel_get(&g->sprite_sheet.sprite_img,
					g->sprite_sheet.sprites[tile_code].coord.x + pallete.x * 200 + tx,
					g->sprite_sheet.sprites[tile_code].coord.y + pallete.y * 186 + ty);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&g->base, point.x * 8 + tx, point.y * 8 + ty,
					color);
			tx++;
		}
		ty++;
	}
}
