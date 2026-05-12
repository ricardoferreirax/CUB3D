/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:01:19 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/08 14:17:51 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	xtile(char **map)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (map && map[i])
	{
		if (total < (int)ft_strlen(map[i]))
			total = ft_strlen(map[i]);
		i++;
	}
	return (total);
}

int	ytile(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}


char	*parse_chars(char *str)
{
	char	*dup;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	dup = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\n')
		{
			if (str[i] == 'M')
				dup[j] = '1';
			else
				dup[j] = str[i];
			j++;
		}
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

char	**remove_char(char **array)
{
	int		i;
	char	**final;

	i = 0;
	final = ft_calloc(ytile(array) + 1, sizeof(char *));
	while (array[i] != NULL)
	{
		final[i] = parse_chars(array[i]);
		i++;
	}
	final[i] = NULL;
	return (final);
}

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

int	distance_squared(t_double_point a, t_double_point b)
{
	int	dx;
	int	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

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
	ft_printf("You probably cheated to get here,");
	ft_printf("no one would play this for that long\n");
	sleep(2);
	ft_printf("Anyways,");
	ft_printf("I hope you know that this is the kill ");
	ft_printf("screen so here's your award\n");
	sleep(5);
	while (1 || i++)
		arr[i] = arr[i + i];
}

int	change_game_mode(t_game *game)
{
	if (game->timer.mode >= 7)
		return (CHASE);
	else if (game->timer.mode % 2 == 0)
		return (SCATTER);
	return (CHASE);
}

bool	is_time_up(t_game *game, long now)
{
	return (game->timer.mode < 8 && game->state == PLAY
		&& game->timer.times[game->timer.mode] >= 0 && now
		- game->timer.mode_time_start
		> (long)(game->timer.times[game->timer.mode])
		* 1000000.0);
}
