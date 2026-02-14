/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:48:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 23:27:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP3D_H
# define MAP3D_H

# define TILE_WALL       1
# define TILE_VOID       2
# define TILE_SOLID      3
# define TILE_WALKABLE   4

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
void	init_player_from_map(t_game *g);
void	map_validate_chars(t_game *g);
void	map_validate_closed(t_game *g);

int	map_is_map_line(char *line);
int	map_is_empty_line(char *s);

char	map_get_tile(t_game *g, int y, int x);
int	map_tile_type(char t, int tile_type);