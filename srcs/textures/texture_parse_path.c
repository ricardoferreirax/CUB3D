/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:19:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 21:20:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../render/render3D.h"
#include "textures3D.h"

static int	parse_cube_texture_line(t_game *g, char *p)
{
	if (!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.no, p + 2, g), 1);
	if (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.so, p + 2, g), 1);
	if (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.we, p + 2, g), 1);
	if (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (set_texture_path(&g->tex.ea, p + 2, g), 1);
	if (*p == 'F' && (p[1] == ' ' || p[1] == '\t'))
		return (parse_floor_ceiling_line(g, 'F', p + 1), 1);
	if (*p == 'C' && (p[1] == ' ' || p[1] == '\t'))
		return (parse_floor_ceiling_line(g, 'C', p + 1), 1);
	return (0);
}

static int	parse_pacman_texture_line(t_game *g, char *p)
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

static void	parse_texture_line(t_game *g, char *line)
{
	char	*p;

	p = skip_whitespace(line);
	if (!*p || *p == '\n')
		return ;
	if (parse_cube_texture_line(g, p))
		return ;
	if (g->mode == MODE_PACMAN)
	{
		if (parse_pacman_texture_line(g, p))
			return ;
	}
}

void	parse_texture_path(t_game *g, const char *path)
{
	int		fd;
	char	*line;

	if (g->debug_mode)
		ft_printf("Opening file: %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g, "parse_texture_path() has not found a valid fd");
	while ((line = get_next_line(fd)))
	{
		if (map_is_map_line(g, line))
		{
			free(line);
			break ;
		}
		parse_texture_line(g, line);
		free(line);
	}
	close(fd);
	if (!g->tex.no || !g->tex.so || !g->tex.we || !g->tex.ea)
		exit_game(EXIT_MAP, g, "parse_texture_path() unable find textures E1");
	if (!g->tex.pacdot || !g->tex.energizer || !g->tex.blinky[0]
		|| !g->tex.blinky[1] || !g->tex.pinky[0] || !g->tex.pinky[1]
		|| !g->tex.inky[0] || !g->tex.inky[1] || !g->tex.clyde[0]
		|| !g->tex.clyde[1])
		exit_game(EXIT_MAP, g, "parse_texture_path() unable find textures E2");
}
