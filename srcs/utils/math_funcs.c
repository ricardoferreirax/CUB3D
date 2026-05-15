/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:33:06 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:39:52 by pfreire-         ###   ########.fr       */
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

int	distance_squared(t_double_point a, t_double_point b)
{
	int	dx;
	int	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
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
