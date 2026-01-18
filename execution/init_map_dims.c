/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_dims.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:51:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/18 15:52:04 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	map_height(char **grid)
{
	int	i;

	i = 0;
	while (grid && grid[i])
		i++;
	return (i);
}

void	init_map_dims(t_game *g)
{
	g->map.height = map_height(g->map.grid);
	g->map.width = line_len_no_nl(g->map.grid[0]);
}
