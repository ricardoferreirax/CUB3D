/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:05:27 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/12 11:18:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int	which_wall(char **original_map, t_map map, t_point *coord)
{
	unsigned char	mask;
	int				final;
	char			**temp;

	mask = mask_constructor(&map, coord, '1');
	final = find_sprite(mask);
	temp = copy_map(map.grid);
	map.grid = temp;
	if (!temp)
		return (-1);
	if (final == 0)
		final = disambiguation(player_spawn(original_map), map, *coord);
	if (original_map[coord->y][coord->x] == 'M')
		final = squared_corners(final);
	free_2d((void **)temp);
	return (final);
}

int	which_tile(char **original_map, t_map *map, t_point coord, bool debug)
{
	int	tile;

	if (map->grid[coord.y][coord.x] == '\0')
		return (10);
	if (map->grid[coord.y][coord.x] == '1')
	{
		tile = (which_wall(original_map, *map, &coord));
		if (tile == 0)
			return (rand() % 255);
		return (tile);
	}
	else
	{
		if (debug)
			return (59);
		return (170);
	}
}

void	solve_rand_tile(t_point *sprite_randomizer, t_point *pallete_randomizer,
		int tile_code)
{
	sprite_randomizer->x = 0;
	sprite_randomizer->y = 0;
	pallete_randomizer->x = 1;
	pallete_randomizer->y = 1;
	if (tile_code == 0)
	{
		srand(get_time_us());
		sprite_randomizer->x = rand() % 999;
		sprite_randomizer->y = rand() % 551;
		pallete_randomizer->x = rand() % 4;
		pallete_randomizer->y = rand() % 2;
	}
}

int	find_sprite_and_return(t_game *g, int tx, int ty, int tile_code)
{
	t_point			sprite_randomizer;
	t_point			pallete_randomizer;
	unsigned int	color;
	t_point			pallete;

	solve_rand_tile(&sprite_randomizer, &pallete_randomizer, tile_code);
	pallete.x = MAP_PALLETE_X;
	pallete.y = MAP_PALLETE_Y;
	color = pixel_get(&g->sprite_sheet.sprite_img,
			(g->sprite_sheet.sprites[tile_code].coord.x + sprite_randomizer.x)
			+ pallete.x * (pallete_randomizer.x * 200) + tx,
			(g->sprite_sheet.sprites[tile_code].coord.y + sprite_randomizer.y)
			+ pallete.y * (pallete_randomizer.y * 186) + ty);
	return (color);
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
			color = find_sprite_and_return(g, tx, ty, tile_code);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&g->base, (point.x * 8 + tx) % g->win.width,
					(point.y * 8 + ty) % g->win.height, color);
			tx++;
		}
		ty++;
	}
}
