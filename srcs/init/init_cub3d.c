/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:27:11 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/25 17:31:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

void	init_assets(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g);
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
	const char	*path;

	if (!g)
		return ;
	if (mode == MODE_PACMAN)
		path = MAP_PACMAN;
	else
		path = MAP_CUBE;
	switch_mode_and_parse(g, mode, path);
	init_assets(g);
	g->state = PLAY;
}

static void	init_defaults(t_game *g)
{
	if (!g)
		return ;
	ft_bzero(g, sizeof(t_game));
	g->state = MENU;
	g->mode = MODE_PACMAN;
	g->ray.hit_side = -1;
	g->player.target_map_x = -1;
	g->player.target_map_y = -1;
	g->map.floor_color = -1;
	g->map.ceiling_color = -1;
	g->gate_passable = 0;
	g->last_ghost_move_us = 0;
}

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g);
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
	g->ray.sprite_z = malloc(sizeof(double) * g->win.width * g->win.height);
	if (!g->ray.sprite_z)
		exit_game(EXIT_MALLOC, g);
}

void	init_cub3d(t_game *g)
{
	if (!g)
		return ;
	init_defaults(g);
	init_mlx(g);
	start_execution(g);
	load_menu_assets(g);
}
