/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_pacman.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 15:23:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:51:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../render/render3D.h"
#include "textures3D.h"

static int	parse_ghost_texture_line(t_game *g, char *p)
{
	if (!ft_strncmp(p, "BL0", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.blinky[0], p + 3, g), 1);
	if (!ft_strncmp(p, "BL1", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.blinky[1], p + 3, g), 1);
	if (!ft_strncmp(p, "PI0", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.pinky[0], p + 3, g), 1);
	if (!ft_strncmp(p, "PI1", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.pinky[1], p + 3, g), 1);
	if (!ft_strncmp(p, "IN0", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.inky[0], p + 3, g), 1);
	if (!ft_strncmp(p, "IN1", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.inky[1], p + 3, g), 1);
	if (!ft_strncmp(p, "CL0", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.clyde[0], p + 3, g), 1);
	if (!ft_strncmp(p, "CL1", 3) && (p[3] == ' ' || p[3] == '\t'))
		return (set_texture_path(&g->tex.clyde[1], p + 3, g), 1);
	return (0);
}

int	parse_pacman_texture_line(t_game *g, char *p)
{
	if (parse_ghost_texture_line(g, p))
		return (1);
	if (!ft_strncmp(p, "PD", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.pacdot, p + 2, g), 1);
	if (!ft_strncmp(p, "EN", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.energizer, p + 2, g), 1);
	if (!ft_strncmp(p, "GC", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.gate_close, p + 2, g), 1);
	if (!ft_strncmp(p, "SC", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.other_state[0], p + 2, g), 1);
	if (!ft_strncmp(p, "ET", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.other_state[1], p + 2, g), 1);
	return (0);
}

int	parse_floor_ceiling_line(t_game *g, char id, char *value)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		return (0);
	if (id == 'F')
	{
		if (is_xpm_path(value))
			return (set_texture_path(&g->tex.floor, value, g), 1);
		return (parse_floor_ceiling_color(value, &g->map.floor_color));
	}
	else if (id == 'C')
	{
		if (is_xpm_path(value))
			return (set_texture_path(&g->tex.ceiling, value, g), 1);
		return (parse_floor_ceiling_color(value, &g->map.ceiling_color));
	}
	return (0);
}
