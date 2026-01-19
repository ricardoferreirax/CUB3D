/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/16 14:39:51 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAC_STRUCT_H
#define PAC_STRUCT_H

#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>

#define UPDATE_F 16666
#define MAX_UPDATES 5
#define SPEED 75,75757625
#define PLAYER 'J'
#define WALL '1'
#define OPEN_SPACE '0'
#define PACDOT 'D'
#define ENERGIZER 'E'
#define WRAP_PORTS 'W'
#define BLINKY_T 'B'
#define PINKY_T 'P'
#define INKY_T 'I'
#define CLYDE_T 'C'

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
	//each char has only 2 animations for each cardinal direction
	t_image *up[2];
	t_image *down[2];
	t_image *left[2];
	t_image *right[2];
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
	int dir;
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
	FRIGHT,
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

typedef struct s_ghost
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
} t_ghost;
//At game start one of the penhouse ghost will activate it's counter, it will count up each dot pacman eats
//if pacman eats all the dots it gets out, but if the ghost is forced out by timeout its dot counter is not reset and the next ghost dot counter starts counting.


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
	t_timer timer;
	// wen pacman loses a life the ghost's personal dot counter gets deactivated. This Global counter will dictate when a ghost goes out
	// The global counter will check exactly for the values 7, 17 and 32 to release the ghosts. If this value is not exactly it it will no release them
	int global_dot_counter;
	int score;
	int level;
}	t_game;


int xtile(char **map);
int ytile(char **map);

void print_2d(char **map);
t_point chose_next_move(t_ghost *ghost, char **map);
t_point find_c(char **map,  char c);
//init.c and init_aux_funcs.c
void init_game(t_game *game);

long get_time_us(void);
#endif // !DEBUG
