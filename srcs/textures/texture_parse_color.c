/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:31:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "textures3D.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	read_rgb(const char *s, int *i, int *out)
{
	int	n;

	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] < '0' || s[*i] > '9')
		return (0);
	n = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
	}
	if (n > 255)
		return (0);
	*out = n;
	return (1);
}

int	parse_floor_ceiling_color(const char *s, int *dest)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (*dest != -1)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!read_rgb(s, &i, &r) || s[i] != ',')
		return (0);
	if (!read_rgb(s, ++i, &g) || s[i] != ',')
		return (0);
	if (!read_rgb(s, ++i, &b))
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] && s[i] != '\n')
		return (0);
	*dest = rgb_to_int(r, g, b);
	return (1);
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
