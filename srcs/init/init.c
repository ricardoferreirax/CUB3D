/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/05 21:59:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map3D.h"
#include "../player/player3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

t_elroy	set_values(int one_speed, int one_dots, int two_speed, int two_dots)
{
	t_elroy return_val;

	return_val.one.speed_multiplier = one_speed;
	return_val.one.dots_left = one_dots;
	return_val.two.speed_multiplier = two_speed;
	return_val.two.dots_left = two_dots;
	return return_val;
}

const t_lvl_config g_lvl_config[21] =
{
	{(t_elroy){.is_blinky = 1, .one.dots_left = 20, .one.speed_multiplier = 80, .two.dots_left = 10, .two.speed_multiplier = 85}, .ghost_speed = 75, .ghost_frightened_speed = 50, .ghost_tunnel_speed = 40, .pacman_speed = 80, .pacman_frightened_speed = 90, .frightened_time = 6.0, .bonus_fruit_points = 100},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 30, .one.speed_multiplier = 90, .two.dots_left = 15, .two.speed_multiplier = 95}, .ghost_speed = 85, .ghost_frightened_speed = 55, .ghost_tunnel_speed = 45, .pacman_speed = 90, .pacman_frightened_speed = 95, .frightened_time = 5.0, .bonus_fruit_points = 300},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 40, .one.speed_multiplier = 90, .two.dots_left = 20, .two.speed_multiplier = 95}, .ghost_speed = 85, .ghost_frightened_speed = 55, .ghost_tunnel_speed = 45, .pacman_speed = 90, .pacman_frightened_speed = 95, .frightened_time = 4.0, .bonus_fruit_points = 500},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 40, .one.speed_multiplier = 90, .two.dots_left = 20, .two.speed_multiplier = 95}, .ghost_speed = 85, .ghost_frightened_speed = 55, .ghost_tunnel_speed = 45, .pacman_speed = 90, .pacman_frightened_speed = 95, .frightened_time = 3.0, .bonus_fruit_points = 500},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 40, .one.speed_multiplier = 100, .two.dots_left = 20, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 2.0, .bonus_fruit_points = 700},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 50, .one.speed_multiplier = 100, .two.dots_left = 25, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 5.0, .bonus_fruit_points = 700},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 50, .one.speed_multiplier = 100, .two.dots_left = 25, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 2.0, .bonus_fruit_points = 1000}, 
	{(t_elroy){.is_blinky = 1, .one.dots_left = 50, .one.speed_multiplier = 100, .two.dots_left = 25, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 2.0, .bonus_fruit_points = 1000}, 
	{(t_elroy){.is_blinky = 1, .one.dots_left = 60, .one.speed_multiplier = 100, .two.dots_left = 30, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 2000}, 
	{(t_elroy){.is_blinky = 1, .one.dots_left = 60, .one.speed_multiplier = 100, .two.dots_left = 30, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 5.0, .bonus_fruit_points = 2000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 60, .one.speed_multiplier = 100, .two.dots_left = 30, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 2.0, .bonus_fruit_points = 3000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 80, .one.speed_multiplier = 100, .two.dots_left = 40, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 3000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 80, .one.speed_multiplier = 100, .two.dots_left = 40, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 80, .one.speed_multiplier = 100, .two.dots_left = 40, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 3.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 100, .one.speed_multiplier = 100, .two.dots_left = 50, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 100, .one.speed_multiplier = 100, .two.dots_left = 50, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 100, .one.speed_multiplier = 100, .two.dots_left = 50, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 0.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 100, .one.speed_multiplier = 100, .two.dots_left = 50, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 1.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 120, .one.speed_multiplier = 100, .two.dots_left = 60, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 0.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 120, .one.speed_multiplier = 100, .two.dots_left = 60, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 100, .pacman_frightened_speed = 100, .frightened_time = 0.0, .bonus_fruit_points = 5000},
	{(t_elroy){.is_blinky = 1, .one.dots_left = 120, .one.speed_multiplier = 100, .two.dots_left = 60, .two.speed_multiplier = 105}, .ghost_speed = 95, .ghost_frightened_speed = 60, .ghost_tunnel_speed = 50, .pacman_speed = 90, .pacman_frightened_speed = 100, .frightened_time = 0.0, .bonus_fruit_points = 5000}

};

void set_lvl(t_game *game)
{
	int lvl;

	lvl = game->level - 1;
	if(game->level < 1)
		lvl = 0;
	if(game->level > 21)
		lvl = 20;
	game->timer.frightened_time = g_lvl_config[lvl].frightened_time;
	game->player.speed_multiplier = g_lvl_config[lvl].pacman_speed;
	game->player.frightened_speed = g_lvl_config[lvl].pacman_frightened_speed;
	int i = 0;
	while(i < 4)
	{

		game->ghosts[i].cruiser = g_lvl_config[lvl].elroy;
		if(game->ghosts[i].name == BLINKY)
			game->ghosts[i].cruiser.is_blinky = 1;
		game->ghosts[i].speed_multiplier = g_lvl_config[lvl].ghost_speed;
		game->ghosts[i].speed_frightened = g_lvl_config[lvl].ghost_frightened_speed;
		game->ghosts[i].speed_tunnel = g_lvl_config[lvl].ghost_tunnel_speed;
		i++;
	}
}

void	init_assets(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g, "init_assets() has not found a game");
	texture_load_cube(g);
	texture_load_sprites(g);
	if (g->mode == MODE_PACMAN)
	{
		init_sprites(g);
		init_ghosts(g);
	}
}

void	start_game_mode(t_game *g, t_mode mode)
{
	if (!g)
		return ;
	// TODO: Parse this shit correctly
	// parse(g, "../../maps/Pacman.cub");
	g->mode = mode;
	init_assets(g);
	g->state = PLAY;
}

static void	init_defaults(t_game *g)
{
	if (!g)
		return ;
	g->state = MENU;
	g->mode = MODE_PACMAN;
	g->ray.hit_side = -1;
	g->player.target_map.x = -1;
	g->player.target_map.y = -1;
	g->map.floor_color = -1;
	g->map.ceiling_color = -1;
	g->gate_passable = 0;
}

void	init_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g,
			"init_execution() has not found necessary pointers");
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g,
			"init_execution() has failed to allocate memory E1");
	g->ray.sprite_z = malloc(sizeof(double) * g->win.width * g->win.height);
	if (!g->ray.sprite_z)
		exit_game(EXIT_MALLOC, g,
			"init_execution() had failed to allocate memory E2");
}

void	init_map(t_game *g, const char *path)
{
	parse_texture_path(g, path);
	if (g->map.grid)
		free_2d((void *)g->map.grid);
	g->map.grid = load_map_from_cub(g, path);
	if (!g->map.grid)
		exit_game(EXIT_MAP, g, "parse() has not found a grid");
	g->map.height = ytile(g->map.grid);
	g->map.width = xtile(g->map.grid);
	map_validate_chars(g);
	// map_validate_closed(g);
	//^ needs to be checked
}

// void init_player(t_game *game)
// {
// 	game->player.pos.pixel_pos = find_c(game->map.grid, 'E');
// }

void	init(t_game *g, char *path)
{
	if (!g)
		return ;
	init_defaults(g);
	init_minilib(g);
	init_map(g, path);
	init_execution(g);
	init_menu(g);
	ft_printf("Loaded %d sprites\n",init_spritesheet(g));
	init_player(g);
	init_base(g);
	set_lvl(g);
}
