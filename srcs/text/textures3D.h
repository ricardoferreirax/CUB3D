/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures3D.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:20:35 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 23:32:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES3D_H
# define TEXTURES3D_H

typedef struct s_game	t_game;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*ceiling;

	t_image	no_img;
	t_image	so_img;
	t_image	we_img;
	t_image	ea_img;
	t_image	floor_img;
	t_image	ceiling_img;
	t_image	pacdot_img;
}	t_textures;

/* protótipos (opcional aqui, ou num header separado) */
void			parse_texture(t_game *g, char *path);
void			texture_load_xpm(t_game *g, t_image *img, const char *path);
void			texture_load_walls(t_game *g);
void			texture_load_floor_ceiling(t_game *g);
void			load_pacdot_texture(t_game *g, char *path);
unsigned int	tex_pixel(t_image *tex, int x, int y);
t_image			*texture_pick_wall(t_game *g);

#endif