/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/24 15:48:25 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map3D.h"
#include "../player/player3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

t_elroy	set_values(int one_speed, int one_dots, int two_speed, int two_dots)
{
	t_elroy	return_val;

	return_val.one.speed_multiplier = one_speed;
	return_val.one.dots_left = one_dots;
	return_val.two.speed_multiplier = two_speed;
	return_val.two.dots_left = two_dots;
	return (return_val);
}
const t_lvl_config g_lvl_config[21] =
{
	{{1, {0, 20, 80}, {0, 10, 85}}, 75, 50, 40, 80, 90, 6.0, 100},
	{{1, {0, 30, 90}, {0, 15, 95}}, 85, 55, 45, 90, 95, 5.0, 300},
	{{1, {0, 40, 90}, {0, 20, 95}}, 85, 55, 45, 90, 95, 4.0, 500},
	{{1, {0, 40, 90}, {0, 20, 95}}, 85, 55, 45, 90, 95, 3.0, 500},
	{{1, {0, 40, 100}, {0, 20, 105}}, 95, 60, 50, 100, 100, 2.0, 700},
	{{1, {0, 50, 100}, {0, 25, 105}}, 95, 60, 50, 100, 100, 5.0, 700},
	{{1, {0, 50, 100}, {0, 25, 105}}, 95, 60, 50, 100, 100, 2.0, 1000},
	{{1, {0, 50, 100}, {0, 25, 105}}, 95, 60, 50, 100, 100, 2.0, 1000},
	{{1, {0, 60, 100}, {0, 30, 105}}, 95, 60, 50, 100, 100, 1.0, 2000},
	{{1, {0, 60, 100}, {0, 30, 105}}, 95, 60, 50, 100, 100, 5.0, 2000},
	{{1, {0, 60, 100}, {0, 30, 105}}, 95, 60, 50, 100, 100, 2.0, 3000},
	{{1, {0, 80, 100}, {0, 40, 105}}, 95, 60, 50, 100, 100, 1.0, 3000},
	{{1, {0, 80, 100}, {0, 40, 105}}, 95, 60, 50, 100, 100, 1.0, 5000},
	{{1, {0, 80, 100}, {0, 40, 105}}, 95, 60, 50, 100, 100, 3.0, 5000},
	{{1, {0, 100, 100}, {0, 50, 105}}, 95, 60, 50, 100, 100, 1.0, 5000},
	{{1, {0, 100, 100}, {0, 50, 105}}, 95, 60, 50, 100, 100, 1.0, 5000},
	{{1, {0, 100, 100}, {0, 50, 105}}, 95, 60, 50, 100, 100, 0.0, 5000},
	{{1, {0, 100, 100}, {0, 50, 105}}, 95, 60, 50, 100, 100, 1.0, 5000},
	{{1, {0, 120, 100}, {0, 60, 105}}, 95, 60, 50, 100, 100, 0.0, 5000},
	{{1, {0, 120, 100}, {0, 60, 105}}, 95, 60, 50, 100, 100, 0.0, 5000},
	{{1, {0, 120, 100}, {0, 60, 105}}, 95, 60, 50, 90, 100, 0.0, 5000}
};

void	set_lvl(t_game *game)
{
	int	lvl;
	int	i;

	lvl = game->level - 1;
	if (game->level < 1)
		lvl = 0;
	if (game->level > 21)
		lvl = 20;
	game->timer.frightened_time = g_lvl_config[lvl].frightened_time;
	game->player.speed_multiplier = g_lvl_config[lvl].pacman_speed;
	game->player.frightened_speed = g_lvl_config[lvl].pacman_frightened_speed;
	i = 0;
	while (i < 4)
	{
		game->ghosts[i].cruiser = g_lvl_config[lvl].elroy;
		if (game->ghosts[i].name == BLINKY)
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
		init_ghosts(g, 0);
	}
}

void	start_game_mode(t_game *g, t_mode mode)
{
	if (!g)
		return ;
	g->mode = mode;
	init_assets(g);
	g->state = PLAY;
	g->key.mouse_hidden = 1;
	g->key.mouse_lock = 1;
	g->timer.start_time = get_time_us();
	center_mouse(g);
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
	g->player.collected_dots = 0;
	g->map.floor_color = -1;
	g->map.ceiling_color = -1;
	g->gate_passable = 0;
	g->level = 1;
	g->timer.mode_timer = 20.0;
	g->global_state = SCATTER;
}

void	init_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g,
			"init_execution() has not found necessary pointers");
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g, "init_execution() has failed to allocate memory E1");
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
}

void	init(t_game *g, char *path)
{
	if (!g)
		return ;
	init_defaults(g);
	init_minilib(g);
	init_map(g, path);
	init_execution(g);
	init_menu(g);
	int sprites = init_spritesheet(g);
	if(g->debug_mode)
		ft_printf("Loaded %d sprites\n", sprites);
	init_player(g, 0);
	init_base(g);
	set_lvl(g);
}
