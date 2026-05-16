/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pacman.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 15:23:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/16 20:20:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../render/render3D.h"
#include "textures3D.h"

static int	parse_ghost_texture_line(t_game *g, char *p)
{
	if (!ft_strncmp(p, "BL0", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.blinky[0], p + 3));
	if (!ft_strncmp(p, "BL1", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.blinky[1], p + 3));
	if (!ft_strncmp(p, "PI0", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.pinky[0], p + 3));
	if (!ft_strncmp(p, "PI1", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.pinky[1], p + 3));
	if (!ft_strncmp(p, "IN0", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.inky[0], p + 3));
	if (!ft_strncmp(p, "IN1", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.inky[1], p + 3));
	if (!ft_strncmp(p, "CL0", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.clyde[0], p + 3));
	if (!ft_strncmp(p, "CL1", 3) && is_token_end(p[3]))
		return (set_texture_path(&g->tex.clyde[1], p + 3));
	return (-1);
}

int	parse_pacman_texture_line(t_game *g, char *p)
{
	int	parse_status;

	parse_status = parse_ghost_texture_line(g, p);
	if (parse_status != -1)
		return (parse_status);
	if (!ft_strncmp(p, "PD", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.pacdot, p + 2));
	if (!ft_strncmp(p, "EN", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.energizer, p + 2));
	if (!ft_strncmp(p, "GC", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.gate_close, p + 2));
	if (!ft_strncmp(p, "SC", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.other_state[0], p + 2));
	if (!ft_strncmp(p, "ET", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.other_state[1], p + 2));
	return (-1);
}

static int	parse_floor_line(t_game *g, char *value)
{
	if (g->map.floor_color != -1 || g->map.floor_path)
		return (TEX_REPEATED);
	if (is_xpm_path(value))
		return (set_texture_path(&g->map.floor_path, value));
	return (parse_floor_ceiling_color(g, value, &g->map.floor_color));
}

static int	parse_ceiling_line(t_game *g, char *value)
{
	if (g->map.ceiling_color != -1 || g->map.ceiling_path)
		return (TEX_REPEATED);
	if (is_xpm_path(value))
		return (set_texture_path(&g->map.ceiling_path, value));
	return (parse_floor_ceiling_color(g, value, &g->map.ceiling_color));
}

int	parse_floor_ceiling_line(t_game *g, char id, char *value)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		return (TEX_INVALID);
	if (id == 'F')
		return (parse_floor_line(g, value));
	if (id == 'C')
		return (parse_ceiling_line(g, value));
	return (TEX_INVALID);
}
