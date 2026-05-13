/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/13 11:52:09 by rmedeiro         ###   ########.fr       */
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

static int	read_rgb_value(t_game *g, const char *s, int *i, int *out)
{
	int	n;

	skip_spaces(s, i);
	if (s[*i] == '-')
		exit_game(EXIT_MAP, g, "read_rgb_value: RGB cannot be negative");
	if (s[*i] < '0' || s[*i] > '9')
		exit_game(EXIT_MAP, g, "read_rgb_value: expected RGB number");
	n = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
	}
	if (n > 255)
		exit_game(EXIT_MAP, g, "read_rgb_value: RGB value out of range");
	*out = n;
	return (1);
}

static void	expect_comma(t_game *g, const char *s, int *i)
{
	skip_spaces(s, i);
	if (s[*i] != ',')
		exit_game(EXIT_MAP, g, "color error: expected comma");
	(*i)++;
}

int	parse_floor_ceiling_color(t_game *g, const char *s, int *dest)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	if (*dest != -1)
		exit_game(EXIT_MAP, g, "color error: duplicated F/C color");
	i = 0;
	read_rgb_value(g, s, &i, &red);
	expect_comma(g, s, &i);
	read_rgb_value(g, s, &i, &green);
	expect_comma(g, s, &i);
	read_rgb_value(g, s, &i, &blue);
	skip_spaces(s, &i);
	if (s[i] && s[i] != '\n')
		exit_game(EXIT_MAP, g, "color error: extra characters after RGB");
	*dest = rgb_to_int(red, green, blue);
	return (1);
}
