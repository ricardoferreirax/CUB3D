/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures3D.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:20:35 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/16 20:39:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES3D_H
# define TEXTURES3D_H

#define TEX_INVALID		-1
#define TEX_OK			1
#define TEX_REPEATED	2
#define TEX_BAD_PATH	3

# include "../../Pac_Struct.h"

typedef struct s_ghost	t_ghost;

void					texture_load_xpm(t_game *g, t_image *img,
							const char *path);
void					texture_load_cube(t_game *g);
void					texture_load_sprites(t_game *g);
unsigned int			tex_pixel(t_image *tex, int x, int y);
t_image					*texture_pick_wall(t_game *g);
int						is_map_start_line(t_game *g, char *line);
int						rgb_to_int(int r, int g, int b);
int						is_xpm_path(const char *s);
void					strip_newline(char *s);
char					*skip_whitespace(char *s);
int						parse_floor_ceiling_line(t_game *g, char id,
							char *value);
void					draw_wall_column(t_game *g, int x);
int						parse_pacman_texture_line(t_game *g, char *p);
void					parse_texture_path(t_game *g, const char *path);
int						parse_floor_ceiling_color(t_game *g, const char *s,
							int *dest);
int						set_texture_path(char **dest, char *value);

int						parse_cube_texture_line(t_game *g, char *p);
int						parse_texture_line(t_game *g, char *line);
void					texture_parse_error(t_game *g, int fd, char *line,
							char *msg);
							
#endif
