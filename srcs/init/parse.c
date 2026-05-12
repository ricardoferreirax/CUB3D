/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:10:32 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/08 14:11:16 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"

int	controller_finder(char *argv)
{
	int		num;
	char	*path;

	num = ft_atoi(argv);
	if (num <= 0)
		return (ft_dprintf(2,
				"Input a valid positive integer for Controller Event ID\n"),
			-1);
	path = ft_strjoin("/dev/input/event", argv);
	ft_printf("Looking for Controller: %s\n", path);
	if (!path)
		return (ft_printf("Malloc Failed?"), -1);
	num = open(path, O_RDONLY | O_NONBLOCK);
	free(path);
	return (num);
}

bool	wrong_args(t_game *game, int ac, char **argv)
{
	int	i;

	i = 2;
	game->debug_mode = false;
	game->controller_fd = -1;
	while (i < ac)
	{
		if (ft_strcmp(argv[i], "debug_mode=y") == 0)
			game->debug_mode = true;
		else
		{
			game->controller_fd = controller_finder(argv[i]);
			if (game->controller_fd < 0)
				return (ft_dprintf(2,
						"Some error finding the controller occured\n"), true);
		}
		i++;
	}
	return (false);
}
