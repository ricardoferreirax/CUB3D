/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/18 16:00:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

char	**map_parser(char **argv)
{
	int		fd;
	char	**grid;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	grid = ft_calloc(26, sizeof(char *));
	if (!grid)
		return (close(fd), NULL);
	i = 0;
	while (i < 25)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		grid[i] = ft_strdup(line);
		free(line);
		if (!grid[i])
		{
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (close(fd), NULL);
		}
		i++;
	}
	grid[i] = NULL;
	close(fd);
	return (grid);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if ((argc > 3 || argc == 1)
		|| (argc == 3 && ft_strcmp(argv[2], "debug_mode=y") != 0))
		return (ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(EXIT_MALLOC, NULL);
	init_defaults(game);
	game->map.grid = map_parser(argv);
	if (!game->map.grid)
		exit_game(EXIT_MAP, game);
	init_mlx(game);
	start_execution(game);
	return (0);
}
