/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pac_Struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/29 22:31:25 by rmedeiro         ###   ########.fr       */
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


#define UPDATE_F 16666
#define MAX_UPDATES 5
#define SPEED 75.75757625

#define ENERGIZER 'R'
#define WRAP_PORTS 'D'
#define BLINKY_T 'B'
#define PINKY_T 'P'
#define INKY_T 'I'
#define CLYDE_T 'C'
#define GHOST_SPAWN 'G'
#define PLAYER 'J'
#define WALL '1'
#define OPEN_SPACE '0'
#define PACDOT '.'
#define VOID ' '

#define PLAYER_SPEED    0.06
#define ROT_SPEED    0.05
#define PLAYER_RADIUS   0.15

//////// MINIMAP TEST ////////

#define MINI_TILE    8     // tamanho de cada tile em pixels
#define MINI_MARGIN  12    // margem do canto

#define C_BG         0x00000000
#define C_WALL       0x00000088
#define C_WALL_SHADE 0x00000055
#define C_DOT        0x00FFFFCC
#define C_ENERGIZER  0x00FFFFFF
#define C_PLAYER     0x00FFFF00
#define C_PORT       0x0000CCFF

////////////////////////////////


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

typedef struct s_anim
{
	//each char has only 2 animations for each cardinal direction
	t_image *up[2];
	t_image *down[2];
	t_image *left[2];
	t_image *right[2];
}	t_anim;

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

// execution - map
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int ceiling_color;
	int floor_color;
}	t_map;

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

typedef struct s_raycasting
{
	double	*z_buffer; // array para armazenar a distância da parede
	double	camera_x; // posição no ecra (-1 a 1) 
	double	ray_dir_x; 
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;  // +1 ou -1 para indicar a direção no eixo x
	int		step_y; // +1 ou -1 para indicar a direção no eixo y
	double	side_dist_x; // distancia do ray atual até a proxima linha vertical (até a proxima parede no eixo x)
	double	side_dist_y; // distancia do ray atual até a proxima linha horizontal (até a proxima parede no eixo y)
	double	delta_dist_x; // distancia que o ray tem que percorrer para ir de uma linha vertical para a proxima (no eixo x) - distancia entre linhas verticais
	double	delta_dist_y; // distancia que o ray tem que percorrer para ir de uma linha horizontal para a proxima (no eixo y) - distancia entre linhas horizontais
	int		hit_side; // 0 = parede vertical, 1 = parede horizontal
	double	perp_wall_dist; // distancia perpendicular a parede

	// drawing limits
	int		draw_start;
	int		draw_end;
}	t_raycasting;

typedef struct s_backcast
{
	int		is_floor;

	double	ray0_x;
	double	ray0_y;
	double	ray1_x;
	double	ray1_y;

	double	cam_z;
	double	p;
	double	row_dist;

	double	step_x;
	double	step_y;

	double	world_x;
	double	world_y;
}	t_backcast;

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

typedef struct s_game
{
	// o que eu preciso para a execução
	void *mlx_ptr;
	t_window win;
	t_map   map;
	t_image	render;
	t_raycasting ray;
	t_player player;
	t_key	key;
	
	bool debug_mode;
	t_ghost *ghost;
	t_pacdot *dot;
	double timeout;
	t_timer timer;
	int global_dot_counter;
	int score;
	int level;
}	t_game;

#endif // !DEBUG

// =========================
// Execution / Game loop
// =========================
void	start_execution(t_game *game);
void	init_defaults(t_game *g);
int		gameloop(t_game *game);
long	get_time_us(void);

// =========================
// Map & Player init
// =========================
void	setup_map_grid(t_game *g);
char	**map_rectangular(t_game *g);
char	**map_read_file(const char *path);
void	wrap_port(t_game *g);
void	validate_map_chars(t_game *g);
void	validate_map_closed(t_game *g);
char	map_tile(t_game *g, int y, int x);
void	init_player_from_map(t_game *g);
int	is_wall_tile(char t);
int	is_void_tile(char t);
int	is_solid_tile(char t);
int	is_walkable_tile(char t);
int	is_valid_wrap_port(t_game *g, int y, int x);
void	render_minimap_test(t_game *g);

// =========================
// Input & Movement
// =========================
void	init_keys(t_game *g);

void	move_radius_check(t_game *g, double x_delta, double y_delta);
void	player_rotation_controller(t_game *g);
void	movement_controller(t_game *g);

// =========================
// Rendering
// =========================
void	render_frame(t_game *game);
void	process_raycasting(t_game *g);
int		register_center_hit(t_game *g, int screen_x, int hit_found);
void	put_pixel_fast(t_image *img, int x, int y, int color);

// =========================
// MLX / Window
// =========================
void	init_mlx(t_game *game);
void	init_window(t_game *s);

// =========================
// Hooks
// =========================
int		handle_close(t_game *g);
int		handle_key_press(int keycode, t_game *g);
int		handle_key_release(int keycode, t_game *g);

// =========================
// Free & Exit
// =========================
void	exit_game(int errcode, t_game *g);
void	free_game(t_game *g);
void	free_tab_tab(char **tab);

// =========================
// Ghost / AI / Utils
// =========================
t_point	chose_next_move(t_ghost *ghost, char **map);
t_point	find_c(char **map, char c);

int		xtile(char **map);
int		ytile(char **map);