/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spritesheet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:33 by pfreire-          #+#    #+#             */
/*   Updated: 2026/03/08 23:07:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"

int	uselesstile(t_point point)
{
	if (point.y == 55)
	{
		if (point.x == 154 || point.x == 163)
			return (1);
	}
	return (0);
}

t_sprite_ref	init_sprite(t_point control)
{
	t_sprite_ref	sprite;

	if (control.y <= 74)
	{
		sprite.coord = control;
		sprite.height = 8;
		sprite.width = 8;
	}
	else
	{
		sprite.coord = control;
		sprite.width = 16;
		sprite.height = 16;
	}
	return (sprite);
}

void	fill_small_sprites(t_game *game, int *i)
{
	t_point	control;

	control.y = 1;
	while (control.y <= 74)
	{
		control.x = 1;
		while (control.x < 199)
		{
			if (!uselesstile(control))
			{
				game->sprite_sheet.sprites[*i].coord = control;
				game->sprite_sheet.sprites[*i].width = 8;
				game->sprite_sheet.sprites[*i].height = 8;
				(*i)++;
			}
			control.x += 9;
		}
		control.y += 9;
	}
}

void	fill_big_sprites(t_game *game, int *i)
{
	t_point	control;

	control.y = 83;
	while (control.y <= 168)
	{
		control.x = 1;
		while (control.x < 170)
		{
			game->sprite_sheet.sprites[*i].coord = control;
			game->sprite_sheet.sprites[*i].width = 16;
			game->sprite_sheet.sprites[*i].height = 16;
			(*i)++;
			control.x += 17;
		}
		control.y += 17;
	}
}

int	init_spritesheet(t_game *game)
{
	int	i;

	i = 0;
	fill_small_sprites(game, &i);
	fill_big_sprites(game, &i);
	game->sprite_sheet.sprite_img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			SPRITE_SHEET, &game->sprite_sheet.sprite_img.width,
			&game->sprite_sheet.sprite_img.height);
	if (!game->sprite_sheet.sprite_img.img_ptr)
		exit(ft_printf("Did not found SpriteSheet.xpm\n"));
	game->sprite_sheet.sprite_img.img_addr = mlx_get_data_addr(game->sprite_sheet.sprite_img.img_ptr,
			&game->sprite_sheet.sprite_img.bpp,
			&game->sprite_sheet.sprite_img.l_len,
			&game->sprite_sheet.sprite_img.endian);
	return (i);
}
