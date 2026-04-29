/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:04:01 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:43:12 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"
#include "../utils/helpers.h"
#include "../base/base.h"

void	init_base(t_game *s)
{
	int				tile;
	t_point			point;
	unsigned int	color;

	t_map parsed_map;
	parsed_map.grid = remove_char(s->map.grid);
	parsed_map.height = s->map.height;
	parsed_map.width = s->map.width - 1;
	color = 0;
	point.x = 0;
	point.y = 0;
	s->base.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width, s->win.height);
	s->base.img_addr = mlx_get_data_addr(s->base.img_ptr, &s->base.bpp,
			&s->base.l_len, &s->base.endian);
	s->base.width = s->map.width * TILE_SIZE;
	s->base.height = s->map.height * TILE_SIZE;
	while (s->map.grid[point.y])
	{
		point.x = 0;
		while (s->map.grid[point.y][point.x])
		{
			tile = which_tile(s->map.grid, &parsed_map, point, s->debug_mode);
			put_tile_inbase(s, tile, color, point);
			point.x++;
		}
		point.y++;
	}
}
