/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:42:45 by pfreire-          #+#    #+#             */
/*   Updated: 2026/01/17 21:21:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "fcntl.h"
# include "stdlib.h"
# include "unistd.h"

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int b);
char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *str);
char	*isolate_line(char *line, char *buffer);

#endif
