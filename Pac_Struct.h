/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:42:49 by pfreire-         ###   ########.fr       */
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
#include "./libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>
//Controller support
#include <linux/input.h>

#define SPRITE_SHEET "./assets/sprites/SpriteSheet.xpm"

#include "srcs/map/map3D.h"
#include "srcs/player/player3D.h"
#include "srcs/hooks/hooks.h"
#define TILE_SIZE 8

#define TEXTURES "./assets/textures/"

#define MAP_PALLETE_X 3
#define MAP_PALLETE_Y 1

#define UPDATE_F 16666
#define MAX_UPDATES 5
#define SPEED 75.5757625
#define PLAYER 'J'
#define WALL '1'
#define OPEN_SPACE '0'
// #define PACDOT 'D'

#define ENERGIZER 'R'
#define WRAP_PORTS 'D'
#define BLINKY_T 'b'
#define PINKY_T 'p'
#define INKY_T 'i'
#define CLYDE_T 'c'
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
	unsigned int *data;
	int stride;
}					t_image;

typedef struct s_fc
{
	double	pos_x;
	double	pos_y;
	double	step_x;
	double	step_y;
	double	dist;
}	t_fc;

typedef struct s_sprite
{
	double	dist; // distancia do sprite ao player
	int		screen_x; // posição horizontal do sprite na tela (coluna onde o centro do sprite deve ser desenhado)
	int		size; // tamanho do sprite projetado na tela 
	int		draw_start_x; // coluna inicial onde o sprite começa a desenhar
	int		draw_end_x; // coluna final onde o sprite termina de desenhar
	int		draw_start_y; // linha inicial onde o sprite começa a desenhar
	int		draw_end_y; // linha final onde o sprite termina de desenhar
	int 	tex_start_x; // coordenada x da textura correspondente à coluna draw_start_x do sprite
	int 	tex_start_y; // coordenada y da textura correspondente à linha draw_start_y do
}	t_sprite;

typedef struct s_raycasting
{
	double	*z_buffer;
	double *sprite_z;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		hit_side;
	char hit_tile;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		draw_start;
	int		draw_end;
	int		hit;
	int		line_h;
}	t_raycasting;

typedef struct s_window
{
	void			*win_ptr;
	int				width;
	int				height;
	int				ntilesx;
	int				ntilesy;
	t_image			frame_buffer;
}					t_window;

typedef struct s_sprite_ref
{
	t_point coord;
	int width;
	int height;
} t_sprite_ref;

typedef struct s_anim_cord
{
	// Coordinates to find the sprites in the sprite sheet.
	// Each entity has 2 animations per direction, they alternate
	t_sprite_ref up[3];
	t_sprite_ref left[3];
	t_sprite_ref down[3];
	t_sprite_ref right[3];
	t_sprite_ref scared[2];
	//Death animation ofr th eplayer has 12 frames
	t_sprite_ref death[12];

} t_anim;

typedef struct s_control
{
	int current_dir;
	int input_buffer;
	// int cycle_count;
} t_control;

typedef struct s_player
{
	// vou precisar para a execução 3D
	
		// vou precisar para a execução 3D
	t_double_point dir;
	t_double_point target_dir;
	t_double_point plane;
	t_double_point target_plane;
	t_point target_map;
	char	target_tile;    // id do tile que o player está a apontar
	char	target_wall_dir; // 'N', 'S', 'E', 'W'
	double	target_dist;   // distância perpendicular
	
	t_pos pos; // para o 2d (tile/pixel)
	int lives;
	int speed_multiplier;
	int collected_dots;
	int frightened_speed;
	t_anim frames;
	t_control controller;
}	t_player;

typedef enum e_ghost
{
	BLINKY,
	PINKY,
	INKY,
	CLYDE,
	DISABLED
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
	int enabled;
	int dots_left;
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
	t_anim *frames;
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
	t_pos	pos;
	double speed;
	int		dot_counter;
	t_point	target_tile;
	int		global_dot_counter_call;
	int		speed_multiplier;
	int		speed_frightened;
	int		speed_tunnel;
	double	speed_accumulador;
	int		is_steping_on_pacdot;
	t_anim	anim;
	int		invalid_dir;
	char	**mental_map;
	t_sprite_ref sprite;
	t_elroy	cruiser;
	e_state	state;
	t_anim frames;

}	t_ghost;

typedef struct s_time
{
	double level_time;
	double mode_timer;
	double mode_time_start;
	//starts when ghosts are in the pen and pac-man refuses to eat dots
	double timeout_timer;
	int energizer;
	double frightened_time;
	double frightened_time_start;
	//timers related to making sure the game updates at 60Hz
	long last_time_up;
	long accumulator;
	long start_time;
}	t_timer;

typedef struct s_pacdot
{
	t_pos pos;
	bool active;
}	t_pacdot;

typedef struct s_sheet
{
	t_sprite_ref *sprites;
	t_image sprite_img;
}	t_sprite_sheet;

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

typedef enum e_player_action
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
}	t_player_action;


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
	char	*blinky[2];
	char	*pinky[2];
	char	*inky[2];
	char	*clyde[2];
	char	*gate_close;
	char *other_state[2];

	t_image	no_img;
	t_image	so_img;
	t_image	we_img;
	t_image	ea_img;
	t_image	floor_img;
	t_image	ceiling_img;
	t_image	pacdot_img;
	t_image	energizer_img;
	t_image	blinky_img[2];
	t_image	pinky_img[2];
	t_image	inky_img[2];
	t_image	clyde_img[2];
	t_image gate_close_img;
	t_image	other_state_img[2];
}	t_textures;

typedef struct s_lvl_config
{
	t_elroy elroy;
	int ghost_speed;
	int ghost_frightened_speed;
	int ghost_tunnel_speed;
	int pacman_speed;
	int pacman_frightened_speed;
	double frightened_time;
	int bonus_fruit_points;
} t_lvl_config;

typedef struct s_interest_points
{
	t_point ghost_house;
	t_point scatter_target[4];
	t_point player_spawn;
} t_target_points;

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
	t_target_points targets;
	t_image	render;
	t_mode mode;
	t_gstate state;
	t_image menu_img;
	t_image base;
	int pacdot_count;
	int	energizer_count;
	int gate_passable;
	
	bool debug_mode;
	double timeout;
	t_timer timer;
	int global_dot_counter;
	int score;
	int level;
	int controller_fd;
	e_state global_state;
	// SpriteShit is 200x186
	t_sprite_sheet sprite_sheet;
}	t_game;

#endif // !DEBUG

int		gameloop(t_game *game);
long	get_time_us(void);
void	switch_mode_and_parse(t_game *g, t_mode mode, const char *path);
void	start_game_mode(t_game *g, t_mode mode);
char	**copy_map(char **map);
t_point	find_c(char **map, char c);
int	ghost_tick_ready(t_game *g, long now);
int	ghost_opposite_dir(int dir);

// =========================
// Free & Exit
// =========================
void	exit_game(int errcode, t_game *g, char *str);
void	free_game(t_game *g);

// =========================
// Ghost / AI / Utils
// =========================
t_point	find_c(char **map, char c);

int		xtile(char **map);
int		ytile(char **map);

int	pixel_get(t_image *data, int x, int y);
int	pixeL_get_coord(t_sprite_sheet *sheet, int i, int x, int y);
void	ft_pixel_put(t_image *s, int x, int y, unsigned int color);

void print_2d(char **arr);
void breakpoint(void);

void reset_game(t_game *game, int is_death);
void change_pallete(t_point pallet_coord, t_anim *frames);
