/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:16:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/01 22:54:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	exit_game(int errcode, t_game *g)
{
	if (errcode == EXIT_QUIT)
		ft_putstr("\nQuitting Pac-Man...\n");
	else if (errcode == EXIT_MALLOC)
		ft_putstr("\nError: malloc failed\n");
	else if (errcode == EXIT_MLX)
		ft_putstr("\nError: MLX failed\n");
	else if (errcode == EXIT_MAP)
		ft_putstr("\nError: map parsing failed\n");
	else if (errcode == EXIT_INPUT)
		ft_putstr("\nError: invalid input\n");
	free_game(g);
	exit(errcode);
}

static void	free_str(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

static void	destroy_img(t_game *g, t_image *img)
{
	if (!g || !g->mlx_ptr || !img)
		return ;
	if (img->img_ptr)
	{
		mlx_destroy_image(g->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}

static void	free_texture_paths(t_game *g)
{
	if (!g)
		return ;
	free_str(&g->tex.no);
	free_str(&g->tex.so);
	free_str(&g->tex.we);
	free_str(&g->tex.ea);
	free_str(&g->tex.floor);
	free_str(&g->tex.ceiling);
	free_str(&g->tex.pacdot);
	free_str(&g->tex.energizer);
	free_str(&g->tex.blinky);
	free_str(&g->tex.pinky);
	free_str(&g->tex.inky);
	free_str(&g->tex.clyde);
	free_str(&g->tex.gate_close);
}

static void	destroy_all_images(t_game *g)
{
	if (!g || !g->mlx_ptr)
		return ;
	destroy_img(g, &g->win.frame_buffer);
	destroy_img(g, &g->menu_img);
	destroy_img(g, &g->tex.no_img);
	destroy_img(g, &g->tex.so_img);
	destroy_img(g, &g->tex.we_img);
	destroy_img(g, &g->tex.ea_img);
	destroy_img(g, &g->tex.floor_img);
	destroy_img(g, &g->tex.ceiling_img);
	destroy_img(g, &g->tex.gate_close_img);
	destroy_img(g, &g->tex.pacdot_img);
	destroy_img(g, &g->tex.energizer_img);
	destroy_img(g, &g->tex.blinky_img);
	destroy_img(g, &g->tex.pinky_img);
	destroy_img(g, &g->tex.inky_img);
	destroy_img(g, &g->tex.clyde_img);
}

static void	free_pacman_arrays(t_game *g)
{
	int	i;

	if (!g)
		return ;
	if (g->pacdots)
	{
		free(g->pacdots);
		g->pacdots = NULL;
	}
	if (g->energizers)
	{
		free(g->energizers);
		g->energizers = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (g->ghosts[i].mental_map)
		{
			free_tab_tab(g->ghosts[i].mental_map);
			g->ghosts[i].mental_map = NULL;
		}
		i++;
	}
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->ray.z_buffer)
		free(g->ray.z_buffer);
	g->ray.z_buffer = NULL;
	if (g->ray.sprite_z)
		free(g->ray.sprite_z);
	g->ray.sprite_z = NULL;
	free_pacman_arrays(g);
	if (g->map.grid)
		free_tab_tab(g->map.grid);
	g->map.grid = NULL;
	destroy_all_images(g);
	if (g->mlx_ptr && g->win.win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win.win_ptr);
	g->win.win_ptr = NULL;
	free_texture_paths(g);
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
		g->mlx_ptr = NULL;
	}
	free(g);
}

void	free_tab_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
