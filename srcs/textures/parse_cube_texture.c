/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:54:17 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 13:55:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures3D.h"

int	parse_cube_texture_line(t_game *g, char *p)
{
	if (!ft_strncmp(p, "NO", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.no, p + 2));
	if (!ft_strncmp(p, "SO", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.so, p + 2));
	if (!ft_strncmp(p, "WE", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.we, p + 2));
	if (!ft_strncmp(p, "EA", 2) && is_token_end(p[2]))
		return (set_texture_path(&g->tex.ea, p + 2));
	if (*p == 'F' && is_token_end(p[1]))
		return (parse_floor_ceiling_line(g, 'F', p + 1));
	if (*p == 'C' && is_token_end(p[1]))
		return (parse_floor_ceiling_line(g, 'C', p + 1));
	return (-1);
}

int	parse_texture_line(t_game *g, char *line)
{
	char	*p;
	int		ret;

	p = skip_whitespace(line);
	if (!*p || *p == '\n')
		return (1);
	ret = parse_cube_texture_line(g, p);
	if (ret != -1)
		return (ret);
	if (g->mode == MODE_PACMAN)
	{
		ret = parse_pacman_texture_line(g, p);
		if (ret != -1)
			return (ret);
	}
	return (-1);
}

void	texture_parse_error(t_game *g, int fd, char *line, char *msg)
{
	free(line);
	close(fd);
	exit_game(EXIT_MAP, g, msg);
}
