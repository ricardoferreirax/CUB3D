/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:02:12 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/08 14:17:58 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H
# include "../../Pac_Struct.h"

void	exit_game(int errcode, t_game *g, char *str);
int		xtile(char **map);
int		ytile(char **map);
int		ft_abs(int n);

void	ft_pixel_put(t_image *s, int x, int y, unsigned int color);
void	free_game(t_game *g);
int		pixeL_get_coord(t_sprite_sheet *sheet, int i, int x, int y);
int		pixel_get(t_image *data, int x, int y);
char	**remove_char(char **array);
int		distance_to_target(t_ghost *ghost, int dy, int dx);
int		distance_squared(t_double_point a, t_double_point b);
bool	print_usage(void);

bool	is_time_up(t_game *game, long now);
int		change_game_mode(t_game *game);
void	segfault_func(t_game *game);
void	print_2d(char **arr);
#endif //  HELPERS_H
