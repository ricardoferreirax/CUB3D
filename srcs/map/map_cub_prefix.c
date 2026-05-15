/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cub_prefix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:48:53 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:50:48 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map3D.h"
#include "../Pac_Struct.h"

int	map_cube_mode_prefix(char *p)
{
	if (!p)
		return (0);
	if (!ft_strncmp(p, "NO", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "SO", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "WE", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "EA", 2) && is_token_end(p[2]))
		return (1);
	if (*p == 'F' && is_token_end(p[1]))
		return (1);
	if (*p == 'C' && is_token_end(p[1]))
		return (1);
	return (0);
}

int	map_pacman_mode_prefix_helper(char *p)
{
	if (!ft_strncmp(p, "BL0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "BL1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "PI0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "PI1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "IN0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "IN1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "CL0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "CL1", 3) && is_token_end(p[3]))
		return (1);
	return (0);
}

int	map_pacman_mode_prefix(char *p)
{
	if (!p)
		return (0);
	if (!ft_strncmp(p, "PD", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "EN", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "GC", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "SC", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "ET", 2) && is_token_end(p[2]))
		return (1);
	if (map_pacman_mode_prefix_helper(p))
		return (1);
	return (0);
}

int	map_is_cub_prefix(char *p)
{
	if (map_cube_mode_prefix(p))
		return (1);
	if (map_pacman_mode_prefix(p))
		return (1);
	return (0);
}
