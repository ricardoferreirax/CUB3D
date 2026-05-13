/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:19:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/13 11:21:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "../render/render3D.h"
#include "textures3D.h"

static int	parse_cube_texture_line(t_game *g, char *p)
{
	if (!ft_strncmp(p, "NO", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.no, p + 2, g), 1);
	if (!ft_strncmp(p, "SO", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.so, p + 2, g), 1);
	if (!ft_strncmp(p, "WE", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.we, p + 2, g), 1);
	if (!ft_strncmp(p, "EA", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.ea, p + 2, g), 1);
	if (*p == 'F' && is_token_end(p[1]))
		return (parse_floor_ceiling_line(g, 'F', p + 1));
	if (*p == 'C' && is_token_end(p[1]))
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

static void	texture_parse_error(t_game *g, int fd, char *line, char *msg)
{
	free(line);
	close(fd);
	exit_game(EXIT_MAP, g, msg);
}

static void	parse_texture_file(t_game *g, int fd)
{
	char	*line;
	int		has_content;

	has_content = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_is_empty_line(line))
			has_content = 1;
		if (map_is_map_line(g, line))
		{
			free(line);
			return ;
		}
		if (!parse_texture_line(g, line))
			texture_parse_error(g, fd, line, "parse_texture_path(): invalid");
		free(line);
	}
	if (!has_content)
		texture_parse_error(g, fd, NULL, "parse_texture_path(): empty file");
}

static void	validate_required_textures(t_game *g)
{
	if (!g->tex.no || !g->tex.so || !g->tex.we || !g->tex.ea)
		exit_game(EXIT_MAP, g, "parse_texture_path(): Missing texture");
	if (g->mode == MODE_PACMAN && (!g->tex.pacdot || !g->tex.energizer
			|| !g->tex.blinky[0] || !g->tex.blinky[1]
			|| !g->tex.pinky[0] || !g->tex.pinky[1]
			|| !g->tex.inky[0] || !g->tex.inky[1]
			|| !g->tex.clyde[0] || !g->tex.clyde[1]))
		exit_game(EXIT_MAP, g, "parse_texture_path(): Missing texture Pacman");
}

void	parse_texture_path(t_game *g, const char *path)
{
	int	fd;

	if (g->debug_mode)
		ft_printf("Opening file: %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g, "parse_texture_path(): has not found a valid fd");
	parse_texture_file(g, fd);
	close(fd);
	validate_required_textures(g);
}
