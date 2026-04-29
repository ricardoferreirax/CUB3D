/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:18:28 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/13 12:51:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	put_pixel_fast(t_image *img, int x, int y, int color)
{
	unsigned int	*buf;
	int				stride;

	if (!img || !img->img_addr)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	stride = img->l_len / 4;
	buf = (unsigned int *)img->img_addr;
	buf[y * stride + x] = (unsigned int)color;
}

t_image	*ghost_tex(t_game *g, t_ghost *gh)
{
	int	frame;

	if (!g || !gh)
		return (NULL);
	frame = ghost_anim_frame(gh);
	if(gh->state == FRIGHTENED)
		return(&g->tex.other_state_img[0]);
	if(gh->state == EATEN)
		return(&g->tex.other_state_img[1]);
	if (gh->name == BLINKY)
		return (&g->tex.blinky_img[frame]);
	if (gh->name == PINKY)
		return (&g->tex.pinky_img[frame]);
	if (gh->name == INKY)
		return (&g->tex.inky_img[frame]);
	if (gh->name == CLYDE)
		return (&g->tex.clyde_img[frame]);
	return (NULL);
}

int	ghost_anim_frame(t_ghost *gh)
{
	int	x;
	int	y;

	if (!gh)
		return (0);
	x = (int)(gh->pos.tile_pos.x * 4.0);
	y = (int)(gh->pos.tile_pos.y * 4.0);
	return ((x + y) & 1);
}

int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	fract_pos(double x)
{
	int	i; // guarda a parte inteira de x

	i = (int)x;         // converte x para inteiro ao truncar a parte decimal
	if (x < 0.0 && (double)i != x) // se x for negativo e tiver parte decimal
		i -= 1;       // ajusta a parte inteira para o próximo número inteiro menor
	return (x - (double)i);  // devolve so a parte fracionaria positiva
}
