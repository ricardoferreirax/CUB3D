/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:22:16 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/05 15:04:08 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/helpers.h"
#include "ghosts.h"

int	is_ghost_on_deadend(t_game *game, t_ghost *ghost, int direction[4][2],
		int ignore_walls)
{
	t_point	next_tile;
	int		dir;

	dir = (ghost->invalid_dir + 2) % 4;
	next_tile.y = (ghost->pos.pixel_pos.y / TILE_SIZE) + direction[dir][0];
	next_tile.x = (ghost->pos.pixel_pos.x / TILE_SIZE) + direction[dir][1];
	if (!ignore_walls && in_bounds(&game->map, next_tile)
		&& (game->map.grid[next_tile.y][next_tile.x] == '1'
			|| game->map.grid[next_tile.y][next_tile.x] == 'G'))
	{
		if (passed_center(ghost))
		{
			ghost->invalid_dir = dir;
			dir = (dir + 2) % 4;
		}
	}
	return (dir);
}

t_double_point	continue_travel(t_game *game, t_ghost *ghost, int ignore_walls)
{
	int	dir;
	int	runnning;

	static int direction[4][2] = {
		{-1, 0}, // 0 = up
		{0, -1}, // 1 = left
		{1, 0},  // 2 = down
		{0, 1}   // 3 = right
	};
	dir = (ghost->invalid_dir + 2) % 4; // continue forward
	runnning = 0;
	if (ghost->state == EATEN)
		runnning = 100;
	if (ghost->state == FRIGHTENED)
		ghost->speed_accumulador += ghost->speed_frightened;
	else
		ghost->speed_accumulador += ghost->speed_multiplier + runnning;
	if (ghost->speed_accumulador >= 100)
	{
		ghost->speed_accumulador -= 100;
		dir = is_ghost_on_deadend(game, ghost, direction, ignore_walls);
		return ((t_double_point){.x = ghost->pos.pixel_pos.x
			+ direction[dir][1], .y = ghost->pos.pixel_pos.y
			+ direction[dir][0]});
	}
	return ((t_double_point){.x = ghost->pos.pixel_pos.x,
		.y = ghost->pos.pixel_pos.y});
}

void	ghost_move_pixel(t_ghost *gh, int dx, int dy)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x += dx;
	// adiciona o deslocamento x (pixels) à posição atual do ghost
	gh->pos.pixel_pos.y += dy;
	// adiciona o deslocamento y (pixels) à posição atual do ghost
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	// converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
	// converte a posição y do ghost de pixels para tiles
}

// int	get_weighted_direction(double *weight
bool	cannot_move_up(t_game *game, t_ghost *ghost)
{
	int	x;
	int	y;

	x = ghost->pos.pixel_pos.x / 8;
	y = ghost->pos.pixel_pos.y / 8;
	if (y == game->targets.player_spawn.y)
	{
		if (x > game->targets.player_spawn.x - 4
			&& x < game->targets.player_spawn.x + 4)
			return (true);
	}
	if (y == game->targets.ghost_house.y)
	{
		if (x > game->targets.ghost_house.x - 4
			&& x < game->targets.ghost_house.x + 4)
			return (true);
	}
	return (false);
}

int	rng_machine(void)
{
	int	rng_num;
	int	best_dir;

	best_dir = -1;
	rng_num = rand() % 8192;
	if (rng_num < 1338)
		best_dir = 0;
	else if (rng_num < 3402)
		best_dir = 3;
	else if (rng_num < 5740)
		best_dir = 2;
	else if (rng_num < 8192)
		best_dir = 1;
	return (best_dir);
}

int	chose_frightened_dir(t_ghost *ghost, t_map *map, int direction[4][2])
{
	int		best_dir;
	int		tries;
	t_point	check_dir;

	best_dir = rng_machine();
	tries = 0;
	while (tries < 4)
	{
		check_dir.x = ghost->pos.pixel_pos.x / TILE_SIZE
			+ direction[best_dir][1];
		check_dir.y = ghost->pos.pixel_pos.y / TILE_SIZE
			+ direction[best_dir][0];
		if (in_bounds(map, check_dir)
			&& ((map->grid[check_dir.y][check_dir.x] != '1'
					&& map->grid[check_dir.y][check_dir.x] != 'G')
				&& best_dir != ghost->invalid_dir))
			break ;
		best_dir = (best_dir + 3) % 4;
		tries++;
	}
	return (best_dir);
}

bool	is_not_blocked(t_ghost *ghost, t_map *map, int direction[4][2], int i)
{
	int	y;
	int	x;

	y = ghost->pos.pixel_pos.y / TILE_SIZE + direction[i][0];
	x = ghost->pos.pixel_pos.x / TILE_SIZE + direction[i][1];
	if(!in_bounds(map, (t_point){.x = x, .y = y}))
		return false;
	return (map->grid[y][x] != '1' && map->grid[y][x] != 'G' && i != ghost->invalid_dir);
}

int	squared_distance(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return (dx * dx + dy * dy);
}

int	chose_next_dir(t_ghost *ghost, t_map *map, int direction[4][2])
{
	int		i;
	t_point	target;
	int		dist;
	int		best;
	int		best_dir;

	i = -1;
	best = -1;
	best_dir = -1;
	target = ghost->target_tile;
	while (++i < 4)
	{
		if (is_not_blocked(ghost, map, direction, i))
		{
			dist = squared_distance(ghost->pos.pixel_pos.x / TILE_SIZE
					+ direction[i][1], ghost->pos.pixel_pos.y / TILE_SIZE
					+ direction[i][0], target.x, target.y);
			if (best == -1 || dist < best)
			{
				best = dist;
				best_dir = i;
			}
		}
	}
	return (best_dir);
}

int	chose_next_move(t_game *game, t_ghost *ghost, t_map *map)
{
	int	best_dir;

	int direction[4][2] = {
		{-1, 0}, // up
		{0, -1}, // left
		{1, 0},  // down
		{0, 1}   // right
	};
	best_dir = -1;
	if (!map)
		return (-1);
	if (ghost->state == FRIGHTENED)
		best_dir = chose_frightened_dir(ghost, map, direction);
	else
		best_dir = chose_next_dir(ghost, map, direction);
	if (best_dir == -1)
		best_dir = (ghost->invalid_dir + 2) % 4;
	if (best_dir == 0 && cannot_move_up(game, ghost))
		return (ghost_move_pixel(ghost, direction[(ghost->invalid_dir + 2)
				% 4][1], direction[(ghost->invalid_dir + 2) % 4][0]),
			ghost->invalid_dir);
	ghost_move_pixel(ghost, direction[best_dir][1], direction[best_dir][0]);
	return ((best_dir + 2) % 4);
}

void	ghost_set_pixel_pos(t_ghost *gh, double px, double py)
{
	if (!gh)
		return ;
	gh->pos.pixel_pos.x = px;
	// define a posição x do ghost em pixels
	gh->pos.pixel_pos.y = py;
	// define a posição y do ghost em pixels
	gh->pos.tile_pos.x = (double)gh->pos.pixel_pos.x / (double)TILE_SIZE;
	// converte a posição x do ghost de pixels para tiles
	gh->pos.tile_pos.y = (double)gh->pos.pixel_pos.y / (double)TILE_SIZE;
	// converte a posição y do ghost de pixels para tiles
}

void	goto_penhouse(t_game *game, t_ghost *ghost)
{
	ghost->target_tile = game->targets.ghost_house;
	ghost->speed_multiplier = 99;
}

t_point	pinky_target(t_game *game, int n)
{
	t_point	target;
	int		px;
	int		py;

	px = game->player.pos.tile_pos.x;
	py = game->player.pos.tile_pos.y;
	if (game->player.target_dir.x == 1) // RIGHT
		return ((t_point){px + n, py});
	else if (game->player.target_dir.x == -1) // LEFT
		return ((t_point){px - n, py});
	else if (game->player.target_dir.y == 1) // DOWN
		return ((t_point){px, py + n});
	else // UP (bug!)
		return ((t_point){px - n, py - n});
	return (target);
}

t_point	inky_target(t_game *game)
{
	t_point			pivot;
	t_double_point	blinky;
	t_point			target;
	int				vx;
	int				vy;

	// Step 1: 2 tiles ahead of Pac-Man
	pivot = pinky_target(game, 2);
	// Step 2: Blinky position
	blinky = game->ghosts[BLINKY].pos.tile_pos;
	// Step 3: vector from Blinky to pivot
	vx = pivot.x - blinky.x;
	vy = pivot.y - blinky.y;
	// Step 4: double it
	vx *= 2;
	vy *= 2;
	// Step 5: final target
	target.x = blinky.x + vx;
	target.y = blinky.y + vy;
	return (target);
}

t_point	ghost_pos_intile(t_point pos)
{
	return ((t_point){.x = pos.x * 8, .y = pos.y * 8});
}

t_point	chase_player(t_game *game, t_ghost *ghost)
{
	if (ghost->state == EATEN || ghost->state == FRIGHTENED)
		return (ghost->target_tile);
	if (ghost->name == BLINKY)
		return ((t_point){.x = game->player.pos.tile_pos.x,
			.y = game->player.pos.tile_pos.y});
	if (ghost->name == PINKY)
		return (pinky_target(game, 4));
	if (ghost->name == CLYDE)
	{
		if (distance_squared(ghost->pos.tile_pos,
				game->player.pos.tile_pos) >= 8 * TILE_SIZE)
			return ((t_point){.x = game->player.pos.tile_pos.x,
				.y = game->player.pos.tile_pos.y});
		else
			return ((t_point){.x = game->targets.scatter_target[CLYDE].x,
				.y = game->targets.scatter_target[CLYDE].y});
	}
	if (ghost->name == INKY)
		return (inky_target(game));
	return ((t_point){0, 0});
}

void	update_cruise_elroy(t_game *game, t_ghost *ghost)
{
	int	dots_left;

	dots_left = ft_abs(game->player.collected_dots - game->pacdot_count);
	if (!ghost->cruiser.two.enabled
		&& dots_left <= ghost->cruiser.two.dots_left)
	{
		if (game->debug_mode)
			ft_printf("Blinky is Elroy level 2\n");
		ghost->speed_multiplier = ghost->cruiser.two.speed_multiplier;
		ghost->cruiser.two.enabled = true;
	}
	else if (!ghost->cruiser.one.enabled
		&& dots_left <= ghost->cruiser.one.dots_left)
	{
		if (game->debug_mode)
			ft_printf("Blinky is Elroy level 1\n");
		ghost->speed_multiplier = ghost->cruiser.one.speed_multiplier;
		ghost->cruiser.one.enabled = true;
	}
}

void	update_target(t_game *game, t_ghost *ghost)
{
	if (ghost->state == EATEN)
		goto_penhouse(game, ghost);
	if (ghost->state == SCATTER && (!ghost->cruiser.is_blinky
			|| !(ghost->cruiser.one.enabled || ghost->cruiser.two.enabled)))
		ghost->target_tile = game->targets.scatter_target[ghost->name];
	if (ghost->state == CHASE || (ghost->cruiser.is_blinky
			&& (ghost->cruiser.one.enabled || ghost->cruiser.two.enabled)))
		ghost->target_tile = chase_player(game, ghost);
	if (ghost->cruiser.is_blinky)
		update_cruise_elroy(game, ghost);
}

int	ghost_in_penhouse(t_ghost *ghost, char **map)
{
	t_point	gate;
	int		x;
	int		y;

	if (!ghost || !map)
		return (0);
	gate = find_c(map, GATE);
	if (gate.x < 0 || gate.y < 0) // verifica se o gate foi encontrado
		return (0);
	x = ghost->pos.pixel_pos.x / TILE_SIZE;
	y = ghost->pos.pixel_pos.y / TILE_SIZE;
	if (x < gate.x - 2 || x > gate.x + 3)
		return (0);
	if (y < gate.y || y > gate.y + 3)
		return (0); // se passou, então saiu da penhouse
	return (1);     // está dentro da penhouse
}

bool	can_ghost_exit_penhouse(t_game *game, t_ghost *ghost)
{
	if (ghost->dot_counter < game->player.collected_dots)
		return (true);
	return (false);
}

int	ghost_penhouse_dance(t_game *game, t_ghost *ghost, t_point gate)
{
	t_double_point	next;
	int				top_px;
	int				bottom_px;
	int				y;

	top_px = (gate.y + 1) * TILE_SIZE + TILE_SIZE / 2;
	bottom_px = (gate.y + 3) * TILE_SIZE + TILE_SIZE / 2;
	y = (int)ghost->pos.pixel_pos.y;
	if (can_ghost_exit_penhouse(game, ghost))
		ghost->invalid_dir = 2;
	else if (y <= top_px)
		ghost->invalid_dir = 0;
	else if (y >= bottom_px)
		ghost->invalid_dir = 2;
	next = continue_travel(game, ghost, 1);
	ghost_set_pixel_pos(ghost, next.x, next.y);
	return (0);
}

bool	is_on_penhouse(t_point ghost_pos, t_point gate_pos)
{
	if (ghost_pos.x / 8 == gate_pos.x && ghost_pos.y / 8 == gate_pos.y)
		return (true);
	return (false);
}

int	update_ghost(t_game *game, t_ghost *ghost)
{
	t_double_point	next;

	if (!ghost)
		return (-1);
	if (ghost->name == DISABLED || game->mode == MODE_CUBE)
		return (0);
	if (ghost_in_penhouse(ghost, ghost->mental_map.grid))
		return (ghost_penhouse_dance(game, ghost, find_c(ghost->mental_map.grid,
					'G')));
	if (ghost->state == FRIGHTENED && get_time_us()
		- game->timer.frightened_time_start > (long)(game->timer.frightened_time
			* 1000000.0))
	{
		ghost->state = game->global_state;
		ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
	}
	if (ghost->state == EATEN && is_on_penhouse(ghost->pos.pixel_pos,
			game->targets.ghost_house))
	{
		ghost->state = game->global_state;
		ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
	}
	if (ghost->pos.pixel_pos.x % TILE_SIZE != TILE_SIZE / 2
		|| ghost->pos.pixel_pos.y % TILE_SIZE != TILE_SIZE / 2)
	{
		update_target(game, ghost);
		next = continue_travel(game, ghost, 0);
		ghost_set_pixel_pos(ghost, next.x, next.y);
		return (0);
	}
	ghost->invalid_dir = chose_next_move(game, ghost, &ghost->mental_map);
	if (ghost->invalid_dir == -1)
		return (-1);
	return (0);
}

bool	ghost_ai(t_game *game, t_ghost *ghost)
{
	if (ghost->name == DISABLED)
		return (true);
	ghost_wrap_position(game, ghost);
	update_ghost(game, ghost);
	if (ghost->state != game->global_state && ghost->state != FRIGHTENED
		&& ghost->state != EATEN)
	{
		if (ghost->cruiser.is_blinky && (ghost->cruiser.one.enabled
				|| ghost->cruiser.two.enabled))
			ghost->state = CHASE;
		else
		{
			ghost->state = game->global_state;
			ghost->invalid_dir = (ghost->invalid_dir + 2) % 4;
		}
	}
	return (false);
}
