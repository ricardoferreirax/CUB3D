/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funny_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:32:07 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:32:36 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

bool	print_usage(void)
{
	ft_printf("Unkown arguments found\n");
	ft_printf("Usage: ./cub3d [FILE]... [OPTIONS]...\n");
	ft_printf("Runs Pac-Man 3D using X11\n");
	ft_printf("\n\n\tdebug_mode=y\tRuns the game in Debug Mode\n");
	ft_printf("\t[XX]\t\tSpecify a number for the controller event file.");
	ft_printf(" (see README.md for more details)\n");
	ft_printf("\n\n\tExamples:\n\t./cub3d map.cub 12 debug_mode=y\n");
	ft_printf("\t./cub3d ./path/to/file.cub\n");
	ft_printf("\t./cub3d map.cub debug_mode=y\n");
	return (true);
}

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
	volatile char	*p;

	if (game->level <= 255)
		return ;
	free_game(game);
	sleep(2);
	ft_printf("You acctually managed to reach level 256?\n");
	sleep(2);
	ft_printf("You probably cheated to get here, ");
	ft_printf("no one would play this for that long\n");
	sleep(2);
	ft_printf("Anyways, ");
	ft_printf("I hope you know that this is the kill ");
	ft_printf("screen so here's your award\n");
	sleep(5);
	p = (char *)0;
	*p = 42;
}

void	annouce_disabled(int i)
{
	if (i == 0)
		ft_printf("Blinky was disabled\n");
	if (i == 1)
		ft_printf("Pinky was disabled\n");
	if (i == 2)
		ft_printf("Inky was disabled\n");
	if (i == 3)
		ft_printf("ClydE was disabled\n");
}
