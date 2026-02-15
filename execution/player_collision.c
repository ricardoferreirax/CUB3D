/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:42:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/15 23:01:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	is_wall(t_game *g, int y, int x)
{
	char	t;

	t = map_get_tile(g, y, x);
	return (t == WALL || t == VOID);
}

static void	check_borders(t_game *g)
{
	t_player	*p;
	int			plus_x;
	int			minus_x;
	int			plus_y;
	int			minus_y;

	p = &g->player;
	plus_x = (int)(p->pos_x + PLAYER_RADIUS);
	minus_x = (int)(p->pos_x - PLAYER_RADIUS);
	plus_y = (int)(p->pos_y + PLAYER_RADIUS);
	minus_y = (int)(p->pos_y - PLAYER_RADIUS);
	if (is_wall(g, (int)p->pos_y, minus_x))
		p->pos_x = (minus_x + 1) + PLAYER_RADIUS;
	if (is_wall(g, (int)p->pos_y, plus_x))
		p->pos_x = plus_x - PLAYER_RADIUS;
	if (is_wall(g, minus_y, (int)p->pos_x))
		p->pos_y = (minus_y + 1) + PLAYER_RADIUS;
	if (is_wall(g, plus_y, (int)p->pos_x))
		p->pos_y = plus_y - PLAYER_RADIUS;
}

void	move_radius_check(t_game *g, double x_delta, double y_delta)
{
	g->player.pos_x += x_delta;
	g->player.pos_y += y_delta;
	map_wrap_port(g);
	check_borders(g);
}
