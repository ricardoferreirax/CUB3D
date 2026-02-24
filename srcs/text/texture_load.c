/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:59:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 18:41:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

void	texture_load_xpm(t_game *g, t_image *img, const char *path)
{
	int	w;
	int	h;

	img->img_ptr = mlx_xpm_file_to_image(g->mlx_ptr, (char *)path, &w, &h);
	if (!img->img_ptr)
		exit_game(EXIT_MLX, g);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_len, &img->endian);
	if (!img->img_addr)
		exit_game(EXIT_MLX, g);
	img->width = w;
	img->height = h;
}

void	texture_load_walls(t_game *g)
{
	if (!g->tex.no || !g->tex.so || !g->tex.we || !g->tex.ea)
		exit_game(EXIT_MAP, g);
	texture_load_xpm(g, &g->tex.no_img, g->tex.no);
	texture_load_xpm(g, &g->tex.so_img, g->tex.so);
	texture_load_xpm(g, &g->tex.we_img, g->tex.we);
	texture_load_xpm(g, &g->tex.ea_img, g->tex.ea);
	if (g->mode == MODE_PACMAN)
	{
		if (!g->tex.gate_close)
			exit_game(EXIT_MAP, g);
		texture_load_xpm(g, &g->tex.gate_close_img, g->tex.gate_close);
	}
}

void	texture_load_floor_ceiling(t_game *g)
{
	if (g->tex.floor)
		texture_load_xpm(g, &g->tex.floor_img, g->tex.floor);
	if (g->tex.ceiling)
		texture_load_xpm(g, &g->tex.ceiling_img, g->tex.ceiling);
}

void	texture_load_sprites(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g);
	if (g->mode != MODE_PACMAN)
		return ;
	if (!g->tex.pacdot || !g->tex.energizer
		|| !g->tex.blinky || !g->tex.pinky
		|| !g->tex.inky || !g->tex.clyde)
		exit_game(EXIT_MAP, g);
	texture_load_xpm(g, &g->pacdot_img, g->tex.pacdot);
	texture_load_xpm(g, &g->energizer_img, g->tex.energizer);
	texture_load_xpm(g, &g->tex.blinky_img, g->tex.blinky);
	texture_load_xpm(g, &g->tex.pinky_img, g->tex.pinky);
	texture_load_xpm(g, &g->tex.inky_img, g->tex.inky);
	texture_load_xpm(g, &g->tex.clyde_img, g->tex.clyde);
}
