/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures3D.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:20:35 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/21 22:03:14 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES3D_H
# define TEXTURES3D_H

typedef struct s_ghost	t_ghost;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*ceiling;
	char	*pacdot;
	char	*energizer;
	char	*blinky;
	char	*pinky;
	char	*inky;
	char	*clyde;
	char 	*gate_close;
	char	*gate_open;

	t_image	no_img;
	t_image	so_img;
	t_image	we_img;
	t_image	ea_img;
	t_image	floor_img;
	t_image	ceiling_img;
	t_image	pacdot_img;
	t_image	energizer_img;
	t_image	blinky_img;
	t_image	pinky_img;
	t_image	inky_img;
	t_image	clyde_img;
	t_image gate_close_img;
	t_image	gate_open_img;

}	t_textures;

void			parse_texture(t_game *g, char *path);
void			texture_load_xpm(t_game *g, t_image *img, const char *path);
void			texture_load_walls(t_game *g);
void			texture_load_floor_ceiling(t_game *g);
void	texture_load_sprites(t_game *g);
unsigned int	tex_pixel(t_image *tex, int x, int y);
t_image			*texture_pick_wall(t_game *g);

int	read_rgb(const char *s, int *i, t_game *g);
int rgb_to_int(int r, int g, int b);
int	is_xpm_path(const char *s);
void	strip_newline(char *s);
void	texture_load_walls(t_game *g);
void	texture_load_floor_ceiling(t_game *g);
char	*skip_whitespace(char *s);

#endif
