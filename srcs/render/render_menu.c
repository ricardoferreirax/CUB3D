/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:04:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/02 09:54:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	render_menu(t_game *g)
{
	int	x;
	int	y;

	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		return ;
	mlx_clear_window(g->mlx_ptr, g->win.win_ptr);
	if (!g->menu_img.img_ptr)
		return ;
	x = (g->win.width - g->menu_img.width) / 2;
	y = (g->win.height - g->menu_img.height) / 2;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr, g->menu_img.img_ptr, x,
		y);
}
