/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:19:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 17:28:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

static void	set_texture_path(char **dst, char *value, t_game *g)
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
	// floor and ceiling 
}

void	parse_texture(t_game *g, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(EXIT_MAP, g);

	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
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
}


