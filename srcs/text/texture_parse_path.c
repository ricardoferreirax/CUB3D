/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:19:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 18:32:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

void	set_texture_path(char **dst, char *value, t_game *g)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		exit_game(EXIT_MAP, g);
	if (*dst)
		exit_game(EXIT_MAP, g);
	*dst = ft_strdup(value);
	if (!*dst)
		exit_game(EXIT_MALLOC, g);
}

void	parse_floor_ceiling_color(t_game *g, const char *s, int *dst)
{
	int	i;
	int	r;
	int	gc;
	int	b;

	if (*dst != -1)
		exit_game(EXIT_MAP, g);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	r = read_rgb(s, &i, g);
	if (s[i] != ',')
		exit_game(EXIT_MAP, g);
	i++;
	gc = read_rgb(s, &i, g);
	if (s[i] != ',')
		exit_game(EXIT_MAP, g);
	i++;
	b = read_rgb(s, &i, g);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] && s[i] != '\n')
		exit_game(EXIT_MAP, g);
	*dst = rgb_to_int(r, gc, b);
}

void	parse_floor_ceiling_line(t_game *g, char id, char *value)
{
	value = skip_whitespace(value);
	strip_newline(value);
	if (!*value)
		exit_game(EXIT_MAP, g);
	if (id == 'F')
	{
		if (is_xpm_path(value))
			set_texture_path(&g->tex.floor, value, g);
		else
			parse_floor_ceiling_color(g, value, &g->map.floor_color);
	}
	else if (id == 'C')
	{
		if (is_xpm_path(value))
			set_texture_path(&g->tex.ceiling, value, g);
		else
			parse_floor_ceiling_color(g, value, &g->map.ceiling_color);
	}
}

static void	parse_texture_line(t_game *g, char *line)
{
	char	*p;

	p = skip_whitespace(line);
	if (!*p || *p == '\n')
		return ;
	if (!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.no, p + 2, g);
	else if (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.so, p + 2, g);
	else if (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.we, p + 2, g);
	else if (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.ea, p + 2, g);
	else if (*p == 'F' && (p[1] == ' ' || p[1] == '\t'))
		parse_floor_ceiling_line(g, 'F', p + 1);
	else if (*p == 'C' && (p[1] == ' ' || p[1] == '\t'))
		parse_floor_ceiling_line(g, 'C', p + 1);
	else if (!ft_strncmp(p, "PD", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.pacdot, p + 2, g);
	else if (!ft_strncmp(p, "EN", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.energizer, p + 2, g);
	else if (!ft_strncmp(p, "BL", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.blinky, p + 2, g);
	else if (!ft_strncmp(p, "PI", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.pinky, p + 2, g);
	else if (!ft_strncmp(p, "IN", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.inky, p + 2, g);
	else if (!ft_strncmp(p, "CL", 2) && (p[2] == ' ' || p[2] == '\t'))
		set_texture_path(&g->tex.clyde, p + 2, g);
	else if (!ft_strncmp(p, "GC", 2) && (p[2] == ' ' || p[2] == '\t'))
    	set_texture_path(&g->tex.gate_close, p + 2, g);
}

void	parse_texture(t_game *g, const char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g);
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
		exit_game(EXIT_MAP, g);
	if (g->mode == MODE_PACMAN)
	{
		if (!g->tex.pacdot || !g->tex.energizer || !g->tex.blinky || !g->tex.pinky
			|| !g->tex.inky || !g->tex.clyde || !g->tex.gate_close)
			exit_game(EXIT_MAP, g);
	}
}
