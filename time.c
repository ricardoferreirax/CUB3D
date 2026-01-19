/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:37:42 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/16 14:39:39 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

long get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000000L + tv.tv_usec);
}

