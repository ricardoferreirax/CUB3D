/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghosts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:58 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/25 17:35:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	sq(int a) 
{ 
	return (a * a); 
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int nx;
	int ny;
	int tx;
	int ty;

	nx = ghost->pos.tile_pos.x + dx;
	ny = ghost->pos.tile_pos.y + dy;
	tx = ghost->target_tile.x;
	ty = ghost->target_tile.y;
	return (sq(nx - tx) + sq(ny - ty));
}

static int	ghost_can_step(t_game *g, int y, int x)
{
	char t;

	t = map_get_tile(g, y, x);
	if (t == WALL)
		return (0);
	if (t == GATE && !g->gate_passable)
		return (0);
	return (1);
}

t_point	chose_next_move(t_game *g, t_ghost *ghost)
{
	int		i;
	int		best;
	int		best_dir;
	int		dist;
	t_point	dir;
	int		dirs[4][2] = {
		{-1, 0}, {0, -1}, {1, 0}, {0, 1}
	};

	i = 0;
	best = -1;
	best_dir = -1;
	while (i < 4)
	{
		int ny = ghost->pos.tile_pos.y + dirs[i][0];
		int nx = ghost->pos.tile_pos.x + dirs[i][1];

		if (i != ghost->invalid_dir && ghost_can_step(g, ny, nx))
		{
			dist = distance_to_target(ghost, dirs[i][0], dirs[i][1]);
			if (best == -1 || dist < best)
			{
				best = dist;
				best_dir = i;
			}
		}
		i++;
	}
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	ghost->invalid_dir = (best_dir + 2) % 4;

	dir.y = dirs[best_dir][0];
	dir.x = dirs[best_dir][1];
	return (dir);
}

static void	ghost_step_tile(t_game *g, t_ghost *ghost)
{
	t_point mv;

	mv = chose_next_move(g, ghost);
	ghost->pos.tile_pos.x += mv.x;
	ghost->pos.tile_pos.y += mv.y;
	ghost->sprite_x = (double)ghost->pos.tile_pos.x + 0.5;
	ghost->sprite_y = (double)ghost->pos.tile_pos.y + 0.5;
}

void	update_ghosts(t_game *g)
{
	int i;

	i = 0;
	while (i < 4)
	{
		g->ghosts[i].target_tile.x = g->player.pos.tile_pos.x;
		g->ghosts[i].target_tile.y = g->player.pos.tile_pos.y;
		ghost_step_tile(g, &g->ghosts[i]);
		i++;
	}
}










static void	ghost_set(t_game *g, e_ghost who, int x, int y)
{
	g->ghosts[who].name = who;
	g->ghosts[who].sprite_x = (double)x + 0.5;
	g->ghosts[who].sprite_y = (double)y + 0.5;
	g->ghosts[who].pos.tile_pos.x = x;
	g->ghosts[who].pos.tile_pos.y = y;
}

static void	ghost_fill_from_map(t_game *g)
{
	int		x;
	int		y;
	char	t;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			t = map_get_tile(g, y, x);
			if (t == BLINKY_T)
				ghost_set(g, BLINKY, x, y);
			else if (t == PINKY_T)
				ghost_set(g, PINKY, x, y);
			else if (t == INKY_T)
				ghost_set(g, INKY, x, y);
			else if (t == CLYDE_T)
				ghost_set(g, CLYDE, x, y);
			if (t == BLINKY_T || t == PINKY_T
				|| t == INKY_T || t == CLYDE_T)
				g->map.grid[y][x] = OPEN_SPACE;
		}
	}
}

void	init_ghosts(t_game *g)
{
	if (!g || !g->map.grid)
		return ;
	ghost_fill_from_map(g);
}


/* void init_blinky(t_game *game, t_ghost *blinky)
{
	blinky->target_tile = find_c(game->map.grid, 'B');
	blinky->pos.tile_pos = find_c(blinky->mental_map, 'S');
	blinky->invalid_dir = 3;
}

void init_pinky(t_game *game, t_ghost *pinky)
{
	pinky->target_tile = find_c(game->map.grid, 'P');
	pinky->pos.tile_pos = find_c(pinky->mental_map, 'S');
	pinky->invalid_dir = 3;
}

void init_inky(t_game *game, t_ghost *inky)
{
	inky->target_tile = find_c(game->map.grid, 'I');
	inky->pos.tile_pos = find_c(inky->mental_map, 'S');
	inky->invalid_dir = 3;
}

void init_clyde(t_game *game, t_ghost *clyde)
{
	clyde->target_tile = find_c(game->map.grid, 'C');
	clyde->pos.tile_pos = find_c(clyde->mental_map, 'S');
	clyde->invalid_dir = 3;
} */
