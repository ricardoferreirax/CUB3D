/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/24 12:48:46 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pac_Struct.h"

void	init_window(t_game *s)
{
	s->win.ntilesx = 28;
	s->win.ntilesy = 25; 
	s->win.width = 8 * 28;
	s->win.height = 8 * 25;
	s->win.win_ptr = mlx_new_window(s->mlx_ptr, s->win.width, s->win.height,
			"Pac-Man");
	s->win.frame_buffer.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width,
			s->win.height);
	s->win.frame_buffer.img_addr = \
mlx_get_data_addr(s->win.frame_buffer.img_ptr,
			&s->win.frame_buffer.bpp, &s->win.frame_buffer.l_len,
			&s->win.frame_buffer.endian);
	s->win.frame_buffer.width = s->win.width;
	s->win.frame_buffer.heigth = s->win.height;
}

char **map_parser(char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return NULL;
	char **line_test = ft_calloc(sizeof(char *), 25);
	char *line;
	int i = 0;
	while(i < 25)
	{
		line = get_next_line(fd);
		line_test[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return line_test;
}

int main(int argc, char **argv)
{
	t_game *game;
	if((argc > 3 || argc == 1) || (argc == 3 && (ft_strcmp(argv[2], "debug_mode=y") != 0)))
		return(ft_printf("Wrong args\n"), -1);
	game = malloc(sizeof(t_game));
	game->map = map_parser(argv);
	game->mlx_ptr = mlx_init();
	init_window(game);

}
