/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:59:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 18:11:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	texture_load_xpm(t_game *g, t_image *img, const char *path)
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
}
