/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:18:28 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/15 21:19:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

void	convert_texture_coords(t_fc *fc, t_image *tex, int *tx, int *ty)
{
	double	u;
	double	v;

	u = fc->fx - (int)fc->fx;
	v = fc->fy - (int)fc->fy;
	*tx = (int)(u * (double)tex->width);
	*ty = (int)(v * (double)tex->height);
	if (*tx < 0)
		*tx = 0;
	if (*ty < 0)
		*ty = 0;
	if (*tx >= tex->width)
		*tx = tex->width - 1;
	if (*ty >= tex->height)
		*ty = tex->height - 1;
}
