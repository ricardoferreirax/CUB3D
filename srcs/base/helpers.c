/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:15:41 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/12 11:26:46 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int	squared_corners(int final)
{
	if (final == 148)
		return (63);
	if (final == 82)
		return (19);
	if (final == 85)
		return (21);
	if (final == 149)
		return (65);
	return (final);
}

t_point	player_spawn(char **map)
{
	t_point	pos;
	char	*str;
	int		i;

	str = "NEWS";
	i = 0;
	while (str[i])
	{
		pos = find_c(map, str[i]);
		if (pos.x >= 0 && pos.y >= 0)
			break ;
		i++;
	}
	return (pos);
}
