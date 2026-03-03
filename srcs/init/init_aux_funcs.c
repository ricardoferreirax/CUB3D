/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:21:39 by pfreire-          #+#    #+#             */
/*   Updated: 2026/02/25 16:09:55 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initializer.h"


// static void block_spawn(char **map)
// {
// 	int i = 0;
// 	while(map && map[i])
// 	{
// 		int j = 0;
// 		while(map[i][j])
// 		{
// 			if((map[i][j] == 'S' || map[i][j] == 'J'))
// 			{
// 				map[i - 1][j - 1] = '1';
// 				map[i - 1][j + 1] = '1';
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

char **copy_map(char **map)
{
	char **copy;
	copy = ft_calloc(sizeof(char *), ytile(map) + 1);
	int i = 0;
	while(map && map[i])
	{
		int j = 0;
		copy[i] = ft_calloc(sizeof(char) , ft_strlen(map[i]) + 1);
		while(map[i][j] != '\0')
		{
			if(map[i][j] == 'M')
				copy[i][j] = '1';
			else
				copy[i][j] = map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	// block_spawn(copy);
	// ft_printf("Ghost map:\n");
	// print_2d(copy);
	// ft_printf("--------___--");
	return copy;
}
/*
t_point find_c(char **map,  char c)
{
	t_point cord;
	cord.y = 0;
	while(map && map[cord.y])
	{
		cord.x = 0;
		while(map[cord.y][cord.x])
		{
			if(map[cord.y][cord.x] == c)
				return cord;
			cord.x++;
		}
		cord.y++;
	}
	cord.y = -1;
	cord.x = -1;
	return cord;
}
 */

