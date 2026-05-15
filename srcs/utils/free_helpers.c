/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:34:10 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:39:30 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	free_str(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_texture_paths(t_game *g)
{
	if (!g)
		return ;
	free_str(&g->tex.no);
	free_str(&g->tex.so);
	free_str(&g->tex.we);
	free_str(&g->tex.ea);
	free_str(&g->tex.floor);
	free_str(&g->tex.ceiling);
	free_str(&g->map.floor_path);
	free_str(&g->map.ceiling_path);
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

void	destroy_all_images(t_game *g)
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

void	free_raycast(t_game *g)
{
	if (g->ray.z_buffer)
		free(g->ray.z_buffer);
	g->ray.z_buffer = NULL;
	if (g->ray.sprite_z)
		free(g->ray.sprite_z);
	g->ray.sprite_z = NULL;
	if (g->controller_fd != -1)
		close(g->controller_fd);
}

void	destroy_img(t_game *g, t_image *img)
{
	if (!g || !g->mlx_ptr || !img)
		return ;
	if (img->img_ptr)
	{
		mlx_destroy_image(g->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}
