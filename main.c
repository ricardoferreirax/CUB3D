/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/09 20:54:25 by rmedeiro         ###   ########.fr       */
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
	rect = map_rectangular(g);
	if (!rect)
		exit_game(EXIT_MALLOC, g);
	free_tab_tab(g->map.grid);
	g->map.grid = rect;
	validate_map_chars(g);
	init_player_from_map(g);
	validate_map_closed(g);
}

void	start_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g);
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g);
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
