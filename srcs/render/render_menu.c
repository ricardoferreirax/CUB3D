/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:04:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/25 11:16:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	render_menu(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr)
		return ;
	mlx_clear_window(g->mlx_ptr, g->win.win_ptr);
	if (g->menu_img.img_ptr)
		mlx_put_image_to_window(g->mlx_ptr, g->win.win_ptr, g->menu_img.img_ptr, 0, 0);
}
