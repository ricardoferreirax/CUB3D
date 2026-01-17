/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:16:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/17 13:22:05 by rmedeiro         ###   ########.fr       */
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

void	free_game(t_game *g)
{
	int	i;

	if (!g)
		return ;
	// imagem do frame buffer
	if (g->win.frame_buffer.img_ptr && g->mlx_ptr)
		mlx_destroy_image(g->mlx_ptr, g->win.frame_buffer.img_ptr);
	// window
	if (g->win.win_ptr && g->mlx_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win.win_ptr);
	// mapa
	if (g->map)
	{
		i = 0;
		while (g->map[i])
			free(g->map[i++]);
		free(g->map);
	}
	// outras structs
	free(g);
}
