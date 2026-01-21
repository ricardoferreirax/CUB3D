/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:48:50 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/21 11:41:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

static int	is_center_hit(t_game *g, int hit_found, int screen_x)
{
	int	center_x;

	center_x = g->render.width / 2;
	return (!hit_found && screen_x == center_x && map_tile(g, g->ray.map_y, g->ray.map_x) != OPEN_SPACE);
}

int	register_hit(t_game *g, int screen_x, int hit_found)
{
	char	tile;

	if (!is_center_hit(g, hit_found, screen_x))
		return (hit_found);
	tile = map_tile(g, g->ray.map_y, g->ray.map_x);
	g->player.target_map_x = g->ray.map_x;
	g->player.target_map_y = g->ray.map_y;
	g->player.target_tile = tile;
	if (g->ray.hit_side == 0 && g->ray.ray_dir_x < 0)
		g->player.target_wall_dir = 'W';
	else if (g->ray.hit_side == 0)
		g->player.target_wall_dir = 'E';
	else if (g->ray.hit_side == 1 && g->ray.ray_dir_y < 0)
		g->player.target_wall_dir = 'N';
	else
		g->player.target_wall_dir = 'S';
	if (g->ray.hit_side == 0)
		g->player.target_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->player.target_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	return (1);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->img_addr + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
