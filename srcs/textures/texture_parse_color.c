/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 15:51:35 by rmedeiro         ###   ########.fr       */
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

static int	parse_rgb_color(const char *s, int *i, int *color)
{
	if (!read_rgb(s, i, color))
		return (0);
	if (s[*i] != ',')
		return (0);
	(*i)++;
	return (1);
}

int	parse_floor_ceiling_color(const char *s, int *dest)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	if (*dest != -1)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!parse_rgb_color(s, &i, &red))
		return (0);
	if (!parse_rgb_color(s, &i, &green))
		return (0);
	if (!read_rgb(s, &i, &blue))
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] && s[i] != '\n')
		return (0);
	*dest = rgb_to_int(red, green, blue);
	return (1);
}
