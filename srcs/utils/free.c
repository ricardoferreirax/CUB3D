/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:43:18 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/12 11:34:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	exit_game(int errcode, t_game *g, char *str)
{
	if (str)
		ft_dprintf(2, "\n%s\n", str);
	if (errcode == EXIT_QUIT)
		ft_dprintf(2, "\nQuitting Pac-Man...\n");
	else if (errcode == EXIT_MALLOC)
		ft_dprintf(2, "\nError: malloc failed\n");
	else if (errcode == EXIT_MLX)
		ft_dprintf(2, "\nError: MLX failed\n");
	else if (errcode == EXIT_MAP)
		ft_dprintf(2, "\nError: map parsing failed\n");
	else if (errcode == EXIT_INPUT)
		ft_dprintf(2, "\nError: invalid input\n");
	free_game(g);
	if (errcode == EXIT_QUIT)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
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
	free_str(&g->tex.blinky[0]);
	free_str(&g->tex.blinky[1]);
	free_str(&g->tex.pinky[0]);
	free_str(&g->tex.pinky[1]);
	free_str(&g->tex.inky[0]);
	free_str(&g->tex.inky[1]);
	free_str(&g->tex.clyde[0]);
	free_str(&g->tex.clyde[1]);
	free_str(&g->tex.gate_close);
	free_str(&g->tex.other_state[0]);
	free_str(&g->tex.other_state[1]);
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
	destroy_img(g, &g->tex.blinky_img[0]);
	destroy_img(g, &g->tex.blinky_img[1]);
	destroy_img(g, &g->tex.pinky_img[0]);
	destroy_img(g, &g->tex.pinky_img[1]);
	destroy_img(g, &g->tex.inky_img[0]);
	destroy_img(g, &g->tex.inky_img[1]);
	destroy_img(g, &g->tex.clyde_img[0]);
	destroy_img(g, &g->tex.clyde_img[1]);
	destroy_img(g, &g->tex.other_state_img[0]);
	destroy_img(g, &g->tex.other_state_img[1]);
	destroy_img(g, &g->base);
	destroy_img(g, &g->sprite_sheet.sprite_img);
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
			free_2d((void *)g->ghosts[i].mental_map);
			g->ghosts[i].mental_map = NULL;
		}
		i++;
	}
}

void	free_ghost(t_ghost *ghost)
{
	free_2d((void **)ghost->mental_map);
}

void	free_game(t_game *g)
{
	int	i;

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
		free_2d((void *)g->map.grid);
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
	i = -1;
	while (++i < 4)
		free_ghost(&g->ghosts[i]);
	if (g->controller_fd != -1)
		close(g->controller_fd);
	free(g);
}
