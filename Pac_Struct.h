/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/18 21:11:52 by rmedeiro         ###   ########.fr       */
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

// exit codes
# define EXIT_OK        0
# define EXIT_QUIT      1
# define EXIT_MALLOC    2
# define EXIT_MLX       3
# define EXIT_MAP       4
# define EXIT_INPUT     5

// keycodes
# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_H     104

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
	int				height;
	int				bpp;
	int				l_len;
	int				endian;
	void			*img_ptr;
}					t_image;

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
} t_ghost;

typedef struct s_raycasting
{
	double	*z_buffer; // size = window width

	// per column ray
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	// dda
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	
	int		side; // 0 = hit on X side, 1 = hit on Y side

	// wall distance
	double	perp_wall_dist;

	// draw
	int		draw_start;
	int		draw_end;
}	t_raycasting;

// execution - map
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

// execution - view of player
typedef struct s_view
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_view;

// keys
typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_key;

typedef struct s_game
{
	// o que eu preciso para a execução
	void *mlx_ptr;
	t_window win;
	t_map   map;
	t_view	view;
	t_key 	key;
	t_image	render;
	t_raycasting ray;
	// char **map;

	t_player player;
	bool debug_mode;
	t_ghost *ghost;
	t_pacdot *dot;
	int timeout;
	double timer;
	int global_dot_counter;
	int score;
	int level;
}	t_game;

#endif // !DEBUG

// execution
void	start_execution(t_game *game);
void	init_defaults(t_game *g);
int	game_loop(t_game *g);

void	init_mlx(t_game *game);

// render 3d
void	render_3d(t_game *g);

// init map 3d
void	init_map_3d(t_game *g);
void	init_player_from_map(t_game *g);

// free and exit
void	exit_game(int errcode, t_game *g);
void	free_game(t_game *g);

// hooks
void	init_hooks(t_game *g);
int	handle_close(t_game *g);
int	handle_key_press(int keycode, t_game *g);
int	handle_key_release(int keycode, t_game *g);
void	init_keys(t_game *g);