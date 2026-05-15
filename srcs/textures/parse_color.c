/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 18:39:23 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "textures3D.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

static int	read_rgb_value(const char *s, int *i, int *out)
{
	int	n;

	skip_spaces(s, i);
	if (s[*i] == '-')
		return (0);
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

static int	expect_comma(const char *s, int *i)
{
	skip_spaces(s, i);
	if (s[*i] != ',')
		return (0);
	(*i)++;
	return (1);
}

int	parse_floor_ceiling_color(t_game *g, const char *s, int *dest)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	(void)g;
	if (*dest != -1)
		return (0);
	i = 0;
	if (!read_rgb_value(s, &i, &red))
		return (0);
	if (!expect_comma(s, &i))
		return (0);
	if (!read_rgb_value(s, &i, &green))
		return (0);
	if (!expect_comma(s, &i))
		return (0);
	if (!read_rgb_value(s, &i, &blue))
		return (0);
	skip_spaces(s, &i);
	if (s[i] && s[i] != '\n')
		return (0);
	*dest = rgb_to_int(red, green, blue);
	return (1);
}
