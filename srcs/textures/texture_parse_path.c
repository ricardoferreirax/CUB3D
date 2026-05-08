/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:19:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:27:07 by rmedeiro         ###   ########.fr       */
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
		return (parse_floor_ceiling_line(g, 'F', p + 1));
	if (*p == 'C' && (p[1] == ' ' || p[1] == '\t'))
		return (parse_floor_ceiling_line(g, 'C', p + 1));
	return (0);
}

static int	parse_texture_line(t_game *g, char *line)
{
	char	*p;

	p = skip_whitespace(line);
	if (!*p || *p == '\n')
		return (1);
	if (parse_cube_texture_line(g, p))
		return (1);
	if (g->mode == MODE_PACMAN && parse_pacman_texture_line(g, p))
		return (1);
	return (0);
}

static void	parse_texture_file(t_game *g, int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if (map_is_map_line(g, line))
		{
			free(line);
			return ;
		}
		if (!parse_texture_line(g, line))
		{
			free(line);
			close(fd);
			exit_game(EXIT_MAP, g, "parse_texture_path() invalid config");
		}
		free(line);
	}
}

static void	validate_required_textures(t_game *g)
{
	if (!g->tex.no || !g->tex.so || !g->tex.we || !g->tex.ea)
		exit_game(EXIT_MAP, g, "parse_texture_path() unable find textures E1");
	if (g->mode == MODE_PACMAN && (!g->tex.pacdot || !g->tex.energizer
			|| !g->tex.blinky[0] || !g->tex.blinky[1]
			|| !g->tex.pinky[0] || !g->tex.pinky[1]
			|| !g->tex.inky[0] || !g->tex.inky[1]
			|| !g->tex.clyde[0] || !g->tex.clyde[1]))
		exit_game(EXIT_MAP, g, "parse_texture_path() unable find textures E2");
}

void	parse_texture_path(t_game *g, const char *path)
{
	int	fd;

	if (g->debug_mode)
		ft_printf("Opening file: %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g, "parse_texture_path() has not found a valid fd");
	parse_texture_file(g, fd);
	close(fd);
	validate_required_textures(g);
}
