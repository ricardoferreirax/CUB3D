/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:59:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 17:15:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "textures3D.h"

void	texture_load_xpm(t_game *g, t_image *img, const char *path)
{
	int	fd;
	int	w;
	int	h;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g, "texture_load_xpm: texture path not found");
	close(fd);
	img->img_ptr = mlx_xpm_file_to_image(g->mlx_ptr, (char *)path, &w, &h);
	if (!img->img_ptr)
		exit_game(EXIT_MLX, g, "texture_load_xpm: invalid xpm texture");
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_len,
			&img->endian);
	if (!img->img_addr)
	{
		mlx_destroy_image(g->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		exit_game(EXIT_MLX, g, "texture_load_xpm: failed get texture data");
	}
	img->width = w;
	img->height = h;
}

void	texture_load_cube(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g, "texture_load_cube() given invalid pointers");
	if (!g->tex.no || !g->tex.so || !g->tex.we || !g->tex.ea)
		exit_game(EXIT_MAP, g, "texture_load_cube() given invalid textures");
	texture_load_xpm(g, &g->tex.no_img, g->tex.no);
	texture_load_xpm(g, &g->tex.so_img, g->tex.so);
	texture_load_xpm(g, &g->tex.we_img, g->tex.we);
	texture_load_xpm(g, &g->tex.ea_img, g->tex.ea);
	if (g->map.floor_path)
		texture_load_xpm(g, &g->tex.floor_img, g->map.floor_path);
	if (g->map.ceiling_path)
		texture_load_xpm(g, &g->tex.ceiling_img, g->map.ceiling_path);
}

void	texture_load_sprites(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g, "texture_load_sprites() given invalid pointers");
	if (g->mode != MODE_PACMAN)
		return ;
	if (!g->tex.pacdot || !g->tex.energizer || !g->tex.blinky[0]
		|| !g->tex.blinky[1] || !g->tex.pinky[0] || !g->tex.pinky[1]
		|| !g->tex.inky[0] || !g->tex.inky[1] || !g->tex.clyde[0]
		|| !g->tex.clyde[1])
		exit_game(EXIT_MAP, g, "texture_load_sprites() given invalid textures");
	texture_load_xpm(g, &g->tex.pacdot_img, g->tex.pacdot);
	texture_load_xpm(g, &g->tex.energizer_img, g->tex.energizer);
	texture_load_xpm(g, &g->tex.blinky_img[0], g->tex.blinky[0]);
	texture_load_xpm(g, &g->tex.blinky_img[1], g->tex.blinky[1]);
	texture_load_xpm(g, &g->tex.pinky_img[0], g->tex.pinky[0]);
	texture_load_xpm(g, &g->tex.pinky_img[1], g->tex.pinky[1]);
	texture_load_xpm(g, &g->tex.inky_img[0], g->tex.inky[0]);
	texture_load_xpm(g, &g->tex.inky_img[1], g->tex.inky[1]);
	texture_load_xpm(g, &g->tex.clyde_img[0], g->tex.clyde[0]);
	texture_load_xpm(g, &g->tex.clyde_img[1], g->tex.clyde[1]);
	texture_load_xpm(g, &g->tex.other_state_img[0], g->tex.other_state[0]);
	texture_load_xpm(g, &g->tex.other_state_img[1], g->tex.other_state[1]);
}
