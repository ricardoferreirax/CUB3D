/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:25:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/02 09:53:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZER_H
#define INITIALIZER_H
#include "../../Pac_Struct.h"

void	init_mlx(t_game *game);
void	init_cub3d(t_game *g);
void	init_window(t_game *s);
void	init_assets(t_game *g);
void	init_ghosts(t_game *g);
void	init_sprites(t_game *g);
void	start_execution(t_game *g);

#endif
