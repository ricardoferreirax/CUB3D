/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:39:15 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/13 10:50:19 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ghosts.h"

int	squared_distance(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return (dx * dx + dy * dy);
}
