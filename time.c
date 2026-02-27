/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:37:42 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/27 23:19:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

long get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000000L + tv.tv_usec);
}

int	ghost_tick_ready(t_game *g, long now)
{
	long	elapsed;

	if (!g)
		return (0);
	if (g->timer.last_ghost_us == 0)
		return (g->timer.last_ghost_us = now, 0);
	elapsed = now - g->timer.last_ghost_us;

	/* se isto for ms, 180ms; se for us, 180000us */
	if (elapsed < 10000)
	{
		if (elapsed < 180)
			return (0);
	}
	else
	{
		if (elapsed < 180000)
			return (0);
	}

	g->timer.last_ghost_us = now;
	return (1);
}
