/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_floor_ceiling.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/24 21:27:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "textures3D.h"

int rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	read_rgb(const char *s, int *i, t_game *g)
{
	int	n;

	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] < '0' || s[*i] > '9')
		exit_game(EXIT_MAP, g);
	n = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
	}
	if (n > 255)
		exit_game(EXIT_MAP, g);
	return (n);
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
