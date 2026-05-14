/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 22:12:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:17:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../render/render3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

static int	init_game_grid(t_game *game, char **temp)
{
	int	i;

	game->map.grid = ft_calloc(sizeof(char *), game->map.height + 1);
	if (!game->map.grid)
		return (-1);
	i = 0;
	while (temp && temp[i])
	{
		game->map.grid[i] = ft_calloc(sizeof(char), game->map.width + 1);
		if (!game->map.grid[i])
			return (-1);
		ft_memcpy(game->map.grid[i], temp[i], ft_strlen(temp[i]));
		i++;
	}
	return (0);
}

static void san(char **temp)
{
	int i = 0;
	int j = 0;
	while(temp[j])
	{
		i = 0;
		while(temp[j][i])
		{
			if(temp[j][i] == '\n' && !temp[j][i + 1])
				temp[j][i] = '\0';
			i++;
		}
		j++;
	}
}

void	init_map(t_game *g, const char *path)
{
	char	**temp;

	if (!is_cub_file(path))
		exit_game(EXIT_MAP, g, "Invalid file extension: expected .cub");
	parse_texture_path(g, path);
	if (g->map.grid)
		free_2d((void *)g->map.grid);
	temp = load_map_from_cub(g, path);
	san(temp);
	if (!temp)
		exit_game(EXIT_MAP, g, "parse() has not found a grid");
	g->map.height = ytile(temp);
	g->map.width = xtile(temp);
	if (init_game_grid(g, temp))
		exit_game(EXIT_MALLOC, g, "Something broke");
	free_2d((void **)temp);
	if (g->debug_mode)
		return ;
	map_validate_tiles(g);
	map_validate_wrap_portals(g);
	map_validate_bounds(g);
	map_flood_fill(g);
}
