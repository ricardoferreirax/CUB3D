/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/28 17:04:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

int	gameloop(t_game *game)
{
	long	now;

	now = get_time_us();
	if (game->timer.last_time_up == 0)
	{
		game->timer.last_time_up = now;
		return (0);
	}
	game->timer.last_time_up = now;
	render_frame(game);
	return (0);
}

void	parse_map(t_game *g, const char *path)
{
	char	**rect;

	g->map.grid = map_read_file(path);
	if (!g->map.grid)
		exit_game(EXIT_MAP, g);
	setup_map_grid(g);
	rect = map_rect(g);
	if (!rect)
		exit_game(EXIT_MALLOC, g);
	free_tab_tab(g->map.grid);
	g->map.grid = rect;
	validate_map_chars(g);
	init_player_from_map(g);
	validate_map_closed(g);
	validate_map_flood_fill(g);
}

int main(int argc, char **argv)
{
	t_game *game;
	if((argc > 3 || argc == 1) || (argc == 3 && (ft_strcmp(argv[2], "debug_mode=y") != 0)))
		return(ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(EXIT_MALLOC, NULL);
	init_defaults(game);
	parse_map(game, argv[1]);
	init_mlx(game);
	start_execution(game);
	
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}



// void	clear_terminal(void)
// {
// 	write(1, "\033[H", 3);
// }

// void new_target(t_game *game, t_ghost *ghost, e_state state)
// {
// 	if(state == SCATTER)
// 		ghost->target_tile = find_c(game->map.grid, 'S');
// 	if(state == CHASE)
// 		ghost->target_tile = find_c(game->map.grid, 'J');
// 	if(state == SCATTER)
// 	{
// 		if(ghost->name == BLINKY)
// 			ghost->target_tile = find_c(game->map.grid, 'B');
// 		if(ghost->name == PINKY)
// 			ghost->target_tile = find_c(game->map.grid, 'P');
// 		if(ghost->name == INKY)
// 			ghost->target_tile = find_c(game->map.grid, 'I');
// 		if(ghost->name == CLYDE)
// 			ghost->target_tile = find_c(game->map.grid, 'C');
// 	}
// }

// void update_target(t_game *game)
// {
// 	int i = 0;
// 	while(i < 4)
// 	{
// 		new_target(game, &game->ghost[i], game->ghost[i].state);
// 		i++;
// 	}
// }

// void update_game(t_game *game)
// {
// 	int i = 0;
// 	while(i < 4)
// 	{
// 		t_point next_move = chose_next_move(&game->ghost[i], game->ghost->mental_map);
// 		if(game->ghost[i].is_steping_on_pacdot)
// 			game->map.grid[game->ghost[i].pos.tile_pos.y][game->ghost[i].pos.tile_pos.x] = 'D';
// 		else
// 			game->map.grid[game->ghost[i].pos.tile_pos.y][game->ghost[i].pos.tile_pos.x] = '0';
// 		game->ghost[i].pos.tile_pos.x += next_move.x;
// 		game->ghost[i].pos.tile_pos.y += next_move.y;
// 		game->map.grid[game->ghost[i].pos.tile_pos.y][game->ghost[i].pos.tile_pos.x] = 'L';
// 		i++;
// 	}
// }

// int	keyloop(int key, t_game *game)
// {
// 	if (key == 0 && game->debug_mode)
// 		ft_printf("test");
// 	if (key == 'q' || key == 65307)
// 		ft_printf("test");
// 	else if (key == 0 || key == 0)
// 	{
// 		ft_printf("test");
// 	}
// 	else if (key == 0 || key == 0)
// 	{ 
// 		ft_printf("test");
// 	}
// 	else if (key == 0 || key == 0)
// 	{ 
// 		ft_printf("test");
// 	}
// 	else if (key == 0 || key == 0)
// 	{ 
// 		ft_printf("test");
// 	}
// 	return (0);
// }
