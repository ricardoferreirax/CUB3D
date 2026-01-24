/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:41:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/24 19:45:04 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	checker_color(int tx, int ty, int is_floor)
{
	int	even_sum;

	even_sum = 0;
	if (ft_is_even(tx + ty))
		even_sum = 1;
	if (is_floor)
	{
		if (even_sum)
			return (0x00303030);
		return (0x00404040);
	}
	if (even_sum)
		return (0x00101010);
	return (0x00181818);
}
