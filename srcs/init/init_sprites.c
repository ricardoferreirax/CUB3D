/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:15:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 23:00:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

static int	count_in_map(t_game *g, char target)
{
	int	row;
	int	col;
	int	total;

	if (!g || !g->map.grid)
		return (0);
	row = 0;
	total = 0;
	while (g->map.grid[row])
	{
		col = 0;
		while (g->map.grid[row][col])
		{
			if (g->map.grid[row][col] == target)
				total++;
			col++;
		}
		row++;
	}
	return (total);
}

static void	fill_from_map(t_game *g, t_pacdot *sprites, char target)
{
	int	row;
	int	col;
	int	i;

	row = 0;
	i = 0;
	while (g->map.grid[row])
	{
		col = 0;
		while (g->map.grid[row][col])
		{
			if (g->map.grid[row][col] == target)
			{
				sprites[i].x = (double)col + 0.5;
				sprites[i].y = (double)row + 0.5;
				sprites[i].active = 1;
				sprites[i].eaten = false;
				i++;
			}
			col++;
		}
		row++;
	}
}

static void	init_sprite(t_game *g, char target, t_pacdot **s_arr, int *s_count)
{
	int	total;

	if (!g || !s_arr || !s_count)
		return ;
	*s_arr = NULL;
	*s_count = count_in_map(g, target);
	total = *s_count;
	if (total <= 0)
		return ;
	*s_arr = malloc(sizeof(t_pacdot) * total);
	if (!*s_arr)
		exit_game(EXIT_MALLOC, g, "init_sprites() was unable to allocate memory E1");
	fill_from_map(g, *s_arr, target);
}

void	init_sprites(t_game *g)
{
	init_sprite(g, PACDOT, &g->pacdots, &g->pacdot_count);
	init_sprite(g, ENERGIZER, &g->energizers, &g->energizer_count);
}


void	init_menu(t_game *g)
{

	g->menu_img.img_ptr = mlx_xpm_file_to_image(g->mlx_ptr, "../../assets/textures/menu.xpm", &g->menu_img.width, &g->menu_img.height);
	if (!g->menu_img.img_ptr)
		exit_game(EXIT_MLX, g, "init_menu() was unable to create img_ptr");
	g->menu_img.img_addr = mlx_get_data_addr(g->menu_img.img_ptr, &g->menu_img.bpp,
			&g->menu_img.l_len, &g->menu_img.endian);
	if (!g->menu_img.img_addr)
	{
		mlx_destroy_image(g->mlx_ptr, g->menu_img.img_ptr);
		g->menu_img.img_ptr = NULL;
		exit_game(EXIT_MLX, g, "init_menu() was unable to create img_addr");
	}
}

