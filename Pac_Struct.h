/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/27 00:17:51 by rmedeiro         ###   ########.fr       */
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
#include <sys/time.h>

#include "srcs/map/map3D.h"
#include "srcs/player/player3D.h"
#include "srcs/hooks/hooks.h"

#define UPDATE_F 16666
#define MAX_UPDATES 5
#define SPEED 75.75757625

#define ENERGIZER 'R'
#define WRAP_PORTS 'D'
#define BLINKY_T 'B'
#define PINKY_T 'P'
#define INKY_T 'I'
#define CLYDE_T 'C'
#define GATE 'G'
#define PLAYER 'J'
#define WALL '1'
#define OPEN_SPACE '0'
#define PACDOT '.'
#define VOID ' '

// exit codes
# define EXIT_OK        0
# define EXIT_QUIT      1
# define EXIT_MALLOC    2
# define EXIT_MLX       3
# define EXIT_MAP       4
# define EXIT_INPUT     5

#define MAP_PACMAN "./maps/Pacman.cub"
#define MAP_CUBE   "./maps/cube.cub"

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_double_point
{
	double x;
	double y;
}	t_double_point;

typedef struct s_position
{
	t_point pixel_pos;
	t_double_point tile_pos;
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

# include "srcs/text/textures3D.h"
# include "srcs/render/render3D.h"

typedef struct s_window
{
	void			*win_ptr;
	int				width;
	int				height;
	int				ntilesx;
	int				ntilesy;
	t_image			frame_buffer;
}					t_window;

typedef struct s_anim
{
	//each char has only 2 animations for each cardinal direction
	t_image *up[2];
	t_image *down[2];
	t_image *left[2];
	t_image *right[2];
}	t_anim;

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

typedef struct s_elroy_level
{
	//Elroy becomes active when few dots are left in the maze
	int dots_left;
	//It gains more speed and it stays in chase mode
	int speed_multiplier;
}	t_elroy_level;

typedef struct s_elroy
{
	//Only Blinky can become Elroy Cruiser
	int is_blinky;
	//Elroy has two levels, check table for exact values btu Elroy becomes stronger the less dots there are
	t_elroy_level one;
	t_elroy_level two;
}	t_elroy;

/* typedef struct s_ghost
{
	//Self Explaining, it is the ghost's name
	e_ghost name;
	t_pos pos;
	//dot_counter for the penhouse (not effective for Blinky since he's always out of the penhouse)
	//At game start Pinky, Inky and Clyde make a Queue to leave the penhouse in this order, only one counter can be active at a time see end of struct for more info
	//They can get out in 2 ways, if the dot_counter reaches a certain level or the Player stalls untill the timeout timer (t_time->timeout_timer) triggers
	//the dot_counter goes only up and only resets at level start
	//when the dot_counter limit is reached it gets deactivated but not reset 
	//when the player dies these dot_counter's stay deactivated, the game refers to the global dot counter instead
	int dot_counter;
	t_point target_tile;
	int global_dot_counter_call;
	int speed_multiplier;
	int is_steping_on_pacdot;
	t_anim anim;
	int invalid_dir;
	char **mental_map;
	t_elroy cruiser;
	e_state state;
} t_ghost; */
//At game start one of the penhouse ghost will activate it's counter, it will count up each dot pacman eats
//if pacman eats all the dots it gets out, but if the ghost is forced out by timeout its dot counter is not reset and the next ghost dot counter starts counting.

typedef struct s_ghost
{
	e_ghost	name;
	int	at_center;
	t_pos	pos;
	int		cur_dir;
	int		dot_counter;
	t_point	target_tile;
	int		global_dot_counter_call;
	int		speed_multiplier;
	int		is_steping_on_pacdot;
	t_anim	anim;
	int		invalid_dir;
	char	**mental_map;
	t_elroy	cruiser;
	e_state	state;

}	t_ghost;

typedef struct s_time
{
	double level_time;
	double mode_timer;
	//starts when ghosts are in the pen and pac-man refuses to eat dots
	double timeout_timer;
	int energizer;
	double frightened_time;
	//timers related to making sure the game updates at 60Hz
	long last_time_up;
	long accumulator;
}	t_timer;

typedef struct s_pacdot
{
	double x;
	double y;
	int active;
	
	t_pos pos;
	bool eaten;
}	t_pacdot;

typedef struct s_player
{
	// vou precisar para a execução 3D
	double	pos_x; // posição do player no mapa (eixo X)
	double	pos_y; // posição do player no mapa (eixo Y)
	double	dir_x; // direção para onde o player está a olhar (eixo X)
	double	dir_y; // direção para onde o player está a olhar (eixo Y)
	double	plane_x; // plano (da camera de visao - fov) perpendicular à direção do player (eixo X)
	double	plane_y; // plano (da camera de visao - fov) perpendicular à direção do player (eixo Y)

	int		target_map_x;  	// coordenadas do tile que o player está a apontar no eixo x
	int		target_map_y;  	// coordenadas do tile que o player está a apontar no eixo y
	char	target_tile;    // id do tile que o player está a apontar
	char	target_wall_dir; // 'N', 'S', 'E', 'W'
	double	target_dist;   // distância perpendicular
	
	t_pos pos; // para o 2d (tile/pixel)
	int lives;
	int speed_multiplier;
}	t_player;

typedef enum e_gstate
{
	MENU,
	PLAY
}	t_gstate;

typedef enum e_mode
{
	MODE_CUBE = 0,
	MODE_PACMAN = 1
}	t_mode;

typedef struct s_game
{
	void *mlx_ptr;
	t_window win;
	t_map   map;
	t_raycasting ray;
	t_player player;
	t_key	key;
	t_textures tex;
	t_pacdot *pacdots;
	t_pacdot	*energizers;
	t_ghost		ghosts[4]; 
	t_image	render;
	t_mode mode;
	t_gstate state;
	t_image menu_img;

	int pacdot_count;
	int	energizer_count;
	int gate_passable;
	
	bool debug_mode;
	double timeout;
	t_timer timer;
	int global_dot_counter;
	int score;
	int level;
}	t_game;

#endif // !DEBUG

int		gameloop(t_game *game);
long	get_time_us(void);
void	switch_mode_and_parse(t_game *g, t_mode mode, const char *path);
void	start_game_mode(t_game *g, t_mode mode);
void	ghosts_update_all(t_game *g);

// =========================
// Free & Exit
// =========================
void	exit_game(int errcode, t_game *g);
void	free_game(t_game *g);
void	free_tab_tab(char **tab);

// =========================
// Ghost / AI / Utils
// =========================
t_point	find_c(char **map, char c);

int		xtile(char **map);
int		ytile(char **map);
