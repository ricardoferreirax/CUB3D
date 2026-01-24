/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:48:50 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/24 19:55:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Pac_Struct.h"

// static int	is_center_hit(t_game *g, int hit_found, int screen_x)
// {
// 	int	center_x;

// 	center_x = g->render.width / 2;
// 	return (!hit_found && screen_x == center_x && map_tile(g, g->ray.map_y, g->ray.map_x) != OPEN_SPACE);
// }

static int	is_center_ray(t_game *g, int screen_x)
{
	int	center_x;

	center_x = g->win.width / 2;
	return (screen_x == center_x);
}

static char	hit_dir_char(t_game *g)
{
	if (g->ray.hit_side == 0)
	{
		if (g->ray.ray_dir_x < 0)
			return ('W');
		return ('E');
	}
	else
	{
		if (g->ray.ray_dir_y < 0)
			return ('N');
		return ('S');
	}
}

static double	hit_distance(t_game *g)
{
	if (g->ray.hit_side == 0)
		return (g->ray.side_dist_x - g->ray.delta_dist_x);
	return (g->ray.side_dist_y - g->ray.delta_dist_y);
}

int	register_center_hit(t_game *g, int screen_x, int hit_found)
{
	char	tile;

	if (hit_found)
		return (1);
	if (!is_center_ray(g, screen_x))
		return (0);
	tile = map_tile(g, g->ray.map_y, g->ray.map_x);
	if (tile == OPEN_SPACE)
		return (0);
	g->player.target_map_x = g->ray.map_x;
	g->player.target_map_y = g->ray.map_y;
	g->player.target_tile = tile;
	g->player.target_wall_dir = hit_dir_char(g);
	g->player.target_dist = hit_distance(g);
	return (1);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;
	int		bytes_per_pixel;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	bytes_per_pixel = img->bpp / 8;
	dst = img->img_addr + (y * img->l_len + x * bytes_per_pixel);
	*(unsigned int *)dst = (unsigned int)color;
}

void	clear_image(t_image *img, int ceiling, int floor)
{
	int x;
	int y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (y < img->height / 2)
				put_pixel(img, x, y, ceiling);
			else
				put_pixel(img, x, y, floor);
			x++;
		}
		y++;
	}
}
