/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/11 17:20:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/init/initializer.h"
#include "srcs/map/map3D.h"
#include "srcs/render/render3D.h"
#include "srcs/textures/textures3D.h"
#include "srcs/utils/helpers.h"

void	print_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

void	segfault_func(t_game *game)
{
	char	*arr;
	int		i;

	if (game->level <= 255)
		return ;
	free_game(game);
	arr = NULL;
	i = 0;
	sleep(2);
	ft_printf("You acctually managed to reach level 256?\n");
	sleep(2);
	ft_printf("You probably cheated to get here, no one would play this for that long\n");
	sleep(2);
	ft_printf("Anyways, I hope you know that this is the kill screen so here's your award\n");
	sleep(5);
	while (1 || i++)
		arr[i] = arr[i + i];
}

void	reset_game(t_game *game, int is_death)
{
	int	i;

	sleep(2);
	if (game->mode == MODE_CUBE)
		return ;
	if (is_death)
		game->player.lives--;
	init_player(game, 1);
	init_ghosts(game, 1);
	if (is_death)
		return ;
	i = -1;
	while (++i < game->pacdot_count)
		game->pacdots[i].active = true;
	i = -1;
	while (++i < game->energizer_count)
		game->energizers[i].active = true;
	game->level++;
	if (game->level > 255)
		segfault_func(game);
	game->player.collected_dots = 0;
}

void	controller_player(t_game *game)
{
	struct input_event	event;

	if (game->controller_fd < 0)
		return ;
	while (read(game->controller_fd, &event, sizeof(event)) > 0)
	{
		if (event.type != EV_KEY && event.type != EV_ABS)
			continue ;
		if (event.type == EV_KEY)
		{
			if (event.code == BTN_SOUTH) // Xis
				game->key.down = event.value;
			else if (event.code == BTN_NORTH) // Triangulo
				game->key.up = event.value;
			else if (event.code == BTN_WEST) // Quadrado
				game->key.left = event.value;
			else if (event.code == BTN_EAST) // Bolinha
				game->key.right = event.value;
			// R1 → M
			else if (event.code == BTN_TR)
				game->key.k = event.value;
			else if (event.code == BTN_START)
				game->key.controller_start = event.value;
		}
		if (event.type == EV_ABS)
		{
			// D-pad → WASD
			if (event.code == ABS_HAT0X)
			{
				game->key.a = (event.value == -1);
				game->key.d = (event.value == 1);
			}
			else if (event.code == ABS_HAT0Y)
			{
				game->key.w = (event.value == -1);
				game->key.s = (event.value == 1);
			}
			else if (event.code == ABS_RZ)
				game->key.e = (event.value > 100); // threshold
		}
	}
}

int	gameloop(t_game *game)
{
	long	now;

	controller_player(game);
	now = get_time_us();
	if (game->timer.last_time_up == 0)
	{
		game->timer.last_time_up = now;
		return (0);
	}
	if (now - game->timer.last_time_up < UPDATE_F)
		return (0);
	game->timer.last_time_up = now;
	if (game->timer.mode < 8 && game->state == PLAY
		&& game->timer.times[game->timer.mode] >= 0 && now
		- game->timer.mode_time_start > (long)(game->timer.times[game->timer.mode])
		* 1000000.0)
	{
		if (game->debug_mode)
			printf("Changing Global State at %ld\n", now);
		game->timer.mode++;
		if (game->global_state == SCATTER)
			game->global_state = CHASE;
		else if (game->global_state == CHASE)
			game->global_state = SCATTER;
		game->timer.mode_time_start = now;
	}
	if (game->state == MENU)
		return (game->timer.mode_time_start = now, render_menu(game), 0);
	return (render_frame(game), 0);
}



bool	wrong_args(t_game *game, int ac, char **argv)
{
	int		i;
	char	*path;
	int		num;

	i = 2;
	game->debug_mode = false;
	game->controller_fd = -1;
	while (i < ac)
	{
		if (ft_strcmp(argv[i], "debug_mode=y") == 0)
		{
			ft_printf("Debug Mode is enabled\n");
			game->debug_mode = true;
		}
		else
		{
			num = ft_atoi(argv[i]);
			if (num <= 0)
				return (printf("Input a valid integer for Controller Event ID.\n"), true);
			path = ft_strjoin("/dev/input/event", argv[i]);
			printf("Looking for Controller: %s\n", path);
			if (!path)
				return (printf("Malloc Failed?"), true);
			game->controller_fd = open(path, O_RDONLY | O_NONBLOCK);
			free(path);
			if (game->controller_fd < 0)
				return (printf("Provided ID doesn't exist"), true);
		}
		i++;
	}
	return (false);
}


int	main(int ac, char **av)
{
	t_game	*game;

	if ((ac > 4 || ac < 2))
		return (print_usage(), -1);
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		exit_game(EXIT_MALLOC, NULL, "main() failed to allocate game");
	if (wrong_args(game, ac, av) && print_usage())
		exit_game(EXIT_FAILURE, game, "Wrong Args");
	init(game, av[1]);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
