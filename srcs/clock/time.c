/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:19:08 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:20:52 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"


long get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, (void *)0);
	return(tv.tv_sec * 1000000L + tv.tv_usec);
}
