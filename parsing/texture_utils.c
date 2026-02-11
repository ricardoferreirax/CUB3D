/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:17:53 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/11 13:18:47 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

void	strip_newline(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	s[i] = '\0';
}

char	*skip_whitespace(char *s)
{
	while (s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

int	is_map_start_line(char *line)
{
	return (is_map_line(line));
}


