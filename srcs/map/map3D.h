/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:48:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 22:02:43 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP3D_H
# define MAP3D_H

typedef struct s_game	t_game;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		ceiling_color;
	int		floor_color;
}	t_map;

#endif

void	map_setup_size(t_game *g);
char	**map_rectangular(t_game *g);
char	**load_map_from_cub(t_game *g, const char *path);

char	map_tile(t_game *g, int y, int x);