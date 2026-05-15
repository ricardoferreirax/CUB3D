/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:01:19 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:43:34 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

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
