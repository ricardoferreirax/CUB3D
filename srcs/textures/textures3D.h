/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures3D.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:20:35 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/25 11:06:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES3D_H
# define TEXTURES3D_H

typedef struct s_ghost	t_ghost;

#include "../../Pac_Struct.h"

void	parse_texture_path(t_game *g, const char *path);
void			texture_load_xpm(t_game *g, t_image *img, const char *path);
void	texture_load_cube(t_game *g);
void	texture_load_sprites(t_game *g);
void	set_texture_path(char **dst, char *value, t_game *g);
unsigned int	tex_pixel(t_image *tex, int x, int y);
t_image			*texture_pick_wall(t_game *g);
int	is_map_start_line(t_game *g, char *line);

int	read_rgb(const char *s, int *i, t_game *g);
int rgb_to_int(int r, int g, int b);
int	is_xpm_path(const char *s);
void	strip_newline(char *s);
char	*skip_whitespace(char *s);

#endif
