/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:39:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/04 09:54:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

void	calculate_dda_step(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos_x - g->ray.map_x)
			* g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + TILE_SIZE_3D - g->player.pos_x)
			* g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos_y - g->ray.map_y)
			* g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + TILE_SIZE_3D - g->player.pos_y)
			* g->ray.delta_dist_y;
	}
}

static void	dda_step(t_game *g)
{
	if (g->ray.side_dist_x < g->ray.side_dist_y)
	{
		g->ray.side_dist_x += g->ray.delta_dist_x;
		g->ray.map_x += g->ray.step_x;
		g->ray.hit_side = 0;
	}
	else
	{
		g->ray.side_dist_y += g->ray.delta_dist_y;
		g->ray.map_y += g->ray.step_y;
		g->ray.hit_side = 1;
	}
}

static int	row_last_col_any(t_game *g, int y)
{
	int	last;

	if (!g || !g->map.grid || y < 0 || y >= g->map.height)
		return (-1);
	last = (int)ft_strlen(g->map.grid[y]) - 1;
	while (last >= 0 && (g->map.grid[y][last] == '\n' || g->map.grid[y][last] == '\r'))
		last--;
	return (last);
}

static int	validate_or_wrap_ray(t_game *g)
{
	int	last_wrap;
	int	last_any;

	if (g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
		return (0);
	last_wrap = map_wrap_last_col(g, g->ray.map_y); // se a linha tiver wrap, aplica com base no last da linha do wrap
	if (last_wrap >= 0)
	{
		if (g->ray.map_x < 0)
			g->ray.map_x = last_wrap;
		else if (g->ray.map_x > last_wrap)
			g->ray.map_x = 0;
		return (1);
	}
	last_any = row_last_col_any(g, g->ray.map_y); // se a linha não tiver wrap, valida com base no last da linha
	if (last_any < 0)
		return (0);
	if (g->ray.map_x < 0 || g->ray.map_x > last_any)
		return (0);
	return (1);
}

int	perform_dda(t_game *g)
{
	int		steps;
	int		max_steps;
	char	t;

	steps = 0;
	max_steps = g->map.width * g->map.height + 50;
	while (steps < max_steps)
	{
		dda_step(g);
		if (validate_or_wrap_ray(g) == 0)
			return (0);
		t = map_get_tile(g, g->ray.map_y, g->ray.map_x);
		if (t != GATE)
		{
			if (map_tile_type(t, TILE_SOLID))
				return (g->ray.hit_tile = t, 1);
		}
		else
		{
			if (g->gate_passable == 0)
				return (g->ray.hit_tile = t, 1);
		}
		steps++;
	}
	return (0);
}
