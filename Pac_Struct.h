/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/12 16:29:52 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAC_STRUCT_H
#define PAC_STRUCT_H

#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>

#define SPEED 75,75757625
#define PLAYER 'M'
#define WALL '1'
#define OPEN_SPACE '0'
#define PACDOT 'D'
#define ENERGIZER 'E'
#define WRAP_PORTS 'W'
#define BLINKY_T 'B'
#define PINKY_T 'P'

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_position
{
	t_point pixel_pos;
	t_point tile_pos;
}	t_pos;


typedef struct s_image
{
	char			*img_addr;
	int				width;
	int				heigth;
	int				bpp;
	int				l_len;
	int				endian;
	int				*img_ptr;
}					t_image;

typedef struct s_anim
{
	t_image *up;
	t_image *down;
	t_image *left;
	t_image *right;
}	t_anim;

typedef struct s_window
{
	void			*win_ptr;
	int				width;
	int				height;
	int				ntilesx;
	int				ntilesy;
	t_image			frame_buffer;
}					t_window;

typedef struct s_player
{
	t_pos pos;
	int lives;
	int speed_multiplier;
	t_anim anim;

}	t_player;

typedef struct s_pacdot
{
	t_pos pos;
	bool eaten;
}	t_pacdot;

typedef enum e_ghost
{
	BLINKY,
	PINKY,
	INKY,
	CLYDE
} e_ghost;

typedef enum e_state
{
	CHASE,
	SCATTER,
	FRIGHTENED,
	EATEN,
	SPAWN
}	e_state;

typedef struct s_ghost
{

	e_ghost name;
	t_pos pos;
	int dot_counter;
	t_point target_tile;
	int global_dot_counter_call;
	int speed_multiplier;
	int is_steping_on_pacdot;
	t_anim anim;

} t_ghost;

typedef struct s_game
{
	bool debug_mode;
	void *mlx_ptr;
	t_window win;
	char **map;
	t_ghost *ghost;
	t_pacdot *dot;
	t_player player;
	int timeout;
	double timer;
	int global_dot_counter;
	int score;
	int level;
}	t_game;


int xtile(char **map);
int ytile(char **map);

#endif // !DEBUG
