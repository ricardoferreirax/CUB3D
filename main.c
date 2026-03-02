/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/02 09:51:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"
#include "srcs/init/initializer.h"
#include "srcs/text/textures3D.h"
#include "srcs/render/render3D.h"
#include "srcs/map/map3D.h"


void print_2d(char **arr)
{
	int i = 0;
	while(arr && arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

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
	if (game->state == MENU)
		return (render_menu(game), 0);
	return (render_frame(game), 0);
}

void	switch_mode_and_parse(t_game *g, t_mode mode, const char *path)
{

	char	**rect;

	if (!g || !path)
		exit_game(EXIT_MAP, g);
	g->mode = mode;
	parse_texture_path(g, path);
	if (g->map.grid)
		free_tab_tab(g->map.grid);
	g->map.grid = load_map_from_cub(g, path);
	if (!g->map.grid)
		exit_game(EXIT_MAP, g);
	map_dimensions(g);
	rect = map_rectangular(g);
	if (!rect)
		exit_game(EXIT_MALLOC, g);
	free_tab_tab(g->map.grid);
	g->map.grid = rect;
	map_validate_chars(g);
	init_player_from_map(g);
	map_validate_closed(g);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void)av;
	if ((ac > 3 || ac == 1) || (ac == 3 && (ft_strcmp(av[2], "debug_mode=y") != 0)))
		return (ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(EXIT_MALLOC, NULL);
	init_cub3d(game);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}


