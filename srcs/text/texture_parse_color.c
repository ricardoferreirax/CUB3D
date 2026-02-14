/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:15:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/14 23:25:41 by rmedeiro         ###   ########.fr       */
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
