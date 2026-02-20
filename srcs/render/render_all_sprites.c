/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:09:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/20 22:02:34 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

static double	sprite_dist2(t_game *g, double x, double y)
{
	double	dx;
	double	dy;

	dx = x - g->player.pos_x;
	dy = y - g->player.pos_y;
	return (dx * dx + dy * dy);
}

static void	sprite_ref_store(t_sprite *r, int type, int idx, double dist2)
{
	r->raw_x0 = type;
	r->raw_y0 = idx;
	r->depth = dist2;
}

static int	sprite_refs_add_pacdots(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < g->pacdot_count && n < cap)
	{
		if (g->pacdots && g->pacdots[i].active)
		{
			sprite_ref_store(&list[n], SPR_PACDOT, i,
				sprite_dist2(g, g->pacdots[i].x, g->pacdots[i].y));
			n++;
		}
		i++;
	}
	return (n);
}

static int	sprite_refs_add_energizers(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < g->energizer_count && n < cap)
	{
		if (g->energizers && g->energizers[i].active)
		{
			sprite_ref_store(&list[n], SPR_ENERGIZER, i,
				sprite_dist2(g, g->energizers[i].x, g->energizers[i].y));
			n++;
		}
		i++;
	}
	return (n);
}

static int	sprite_refs_add_ghosts(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < 4 && n < cap)
	{
		sprite_ref_store(&list[n], SPR_GHOST, i,
			sprite_dist2(g, g->ghosts[i].sprite_x, g->ghosts[i].sprite_y));
		n++;
		i++;
	}
	return (n);
}

static void	sprite_refs_sort_far_to_near(t_sprite *s, int n)
{
	int		i;
	int		swapped;
	t_sprite	tmp;

	if (!s || n < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (s[i].depth < s[i + 1].depth)
			{
				tmp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static int	ref_tex_and_div(t_game *g, t_sprite *r, t_image **tex)
{
	int	i;

	i = r->raw_y0;
	if (r->raw_x0 == SPR_PACDOT)
	{
		*tex = &g->pacdot_img;
		return (6);
	}
	if (r->raw_x0 == SPR_ENERGIZER)
	{
		*tex = &g->energizer_img;
		return (3);
	}
	*tex = ghost_tex(g, &g->ghosts[i]);
	return (2);
}

static void	ref_world_xy(t_game *g, t_sprite *r, double *x, double *y)
{
	int	i;

	i = r->raw_y0;
	if (r->raw_x0 == SPR_PACDOT)
	{
		*x = g->pacdots[i].x;
		*y = g->pacdots[i].y;
		return ;
	}
	if (r->raw_x0 == SPR_ENERGIZER)
	{
		*x = g->energizers[i].x;
		*y = g->energizers[i].y;
		return ;
	}
	*x = g->ghosts[i].sprite_x;
	*y = g->ghosts[i].sprite_y;
}

static void	sprite_ref_draw(t_game *g, t_sprite *r)
{
	t_sprite	box;
	t_image		*tex;
	double		x;
	double		y;

	ref_world_xy(g, r, &x, &y);
	if (!sprite_project(g, x, y, &box))
		return ;
	if (!sprite_build(g, &box, ref_tex_and_div(g, r, &tex)))
		return ;
	if (!tex || !tex->img_addr)
		return ;
	sprite_draw(g, &box, tex);
}

void	render_all_sprites(t_game *g)
{
	t_sprite	*refs;
	int			cap;
	int			n;
	int			i;

	if (!g || !g->ray.z_buffer)
		return ;
	cap = g->pacdot_count + g->energizer_count + 4;
	if (cap <= 0)
		return ;
	refs = (t_sprite *)malloc(sizeof(t_sprite) * cap);
	if (!refs)
		return ;
	n = 0;
	n = sprite_refs_add_pacdots(g, refs, n, cap);
	n = sprite_refs_add_energizers(g, refs, n, cap);
	n = sprite_refs_add_ghosts(g, refs, n, cap);
	if (n > 1)
		sprite_refs_sort_far_to_near(refs, n);
	i = 0;
	while (i < n)
	{
		sprite_ref_draw(g, &refs[i]);
		i++;
	}
	free(refs);
}
