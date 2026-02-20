/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:09:52 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/02/20 21:38:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

#define SPR_PACDOT     1
#define SPR_ENERGIZER  2
#define SPR_GHOST      3

static double	dist2_to_player(t_game *g, double x, double y)
{
	double	dx;
	double	dy;

	dx = x - g->player.pos_x;
	dy = y - g->player.pos_y;
	return (dx * dx + dy * dy);
}

/* Guardar "referência" dentro do próprio t_sprite:
   raw_x0 = type, raw_y0 = idx, depth = dist2 (para sorting) */
static void	set_ref(t_sprite *r, int type, int idx, double dist2)
{
	r->raw_x0 = type;
	r->raw_y0 = idx;
	r->depth = dist2;
}

/* ---- Construção da lista (por tipo) ---- */

static int	add_pacdot_refs(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < g->pacdot_count && n < cap)
	{
		if (g->pacdots && g->pacdots[i].active)
		{
			set_ref(&list[n], SPR_PACDOT, i,
				dist2_to_player(g, g->pacdots[i].x, g->pacdots[i].y));
			n++;
		}
		i++;
	}
	return (n);
}

static int	add_energizer_refs(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < g->energizer_count && n < cap)
	{
		if (g->energizers && g->energizers[i].active)
		{
			set_ref(&list[n], SPR_ENERGIZER, i,
				dist2_to_player(g, g->energizers[i].x, g->energizers[i].y));
			n++;
		}
		i++;
	}
	return (n);
}

static int	add_ghost_refs(t_game *g, t_sprite *list, int n, int cap)
{
	int	i;

	i = 0;
	while (i < 4 && n < cap)
	{
		set_ref(&list[n], SPR_GHOST, i,
			dist2_to_player(g, g->ghosts[i].sprite_x, g->ghosts[i].sprite_y));
		n++;
		i++;
	}
	return (n);
}

static void	sort_refs_far_to_near(t_sprite *s, int n)
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

static double	ref_world_x(t_game *g, t_sprite *r)
{
	int	i;

	i = r->raw_y0;
	if (r->raw_x0 == SPR_PACDOT)
		return (g->pacdots[i].x);
	if (r->raw_x0 == SPR_ENERGIZER)
		return (g->energizers[i].x);
	return (g->ghosts[i].sprite_x);
}

static double	ref_world_y(t_game *g, t_sprite *r)
{
	int	i;

	i = r->raw_y0;
	if (r->raw_x0 == SPR_PACDOT)
		return (g->pacdots[i].y);
	if (r->raw_x0 == SPR_ENERGIZER)
		return (g->energizers[i].y);
	return (g->ghosts[i].sprite_y);
}

static int	ref_size_div(t_sprite *r)
{
	if (r->raw_x0 == SPR_PACDOT)
		return (6);
	if (r->raw_x0 == SPR_ENERGIZER)
		return (3);
	return (2);
}

static t_image	*ref_tex(t_game *g, t_sprite *r)
{
	int	i;

	i = r->raw_y0;
	if (r->raw_x0 == SPR_PACDOT)
		return (&g->pacdot_img);
	if (r->raw_x0 == SPR_ENERGIZER)
		return (&g->energizer_img);
	return (ghost_tex(g, &g->ghosts[i]));
}

static void	draw_one_ref(t_game *g, t_sprite *r)
{
	t_sprite	box;
	t_image		*tex;
	int			div;

	tex = ref_tex(g, r);
	div = ref_size_div(r);
	if (!tex || !tex->img_addr)
		return ;
	if (!sprite_project(g, ref_world_x(g, r), ref_world_y(g, r), &box))
		return ;
	if (!sprite_build(g, &box, div))
		return ;
	sprite_draw(g, &box, tex);
}

void	render_all_sprites(t_game *g)
{
	t_sprite	refs[4096];
	int			n;
	int			i;

	if (!g || !g->ray.z_buffer)
		return ;
	n = 0;
	n = add_pacdot_refs(g, refs, n, 4096);
	n = add_energizer_refs(g, refs, n, 4096);
	n = add_ghost_refs(g, refs, n, 4096);
	if (n <= 0)
		return ;
	sort_refs_far_to_near(refs, n);
	i = 0;
	while (i < n)
	{
		draw_one_ref(g, &refs[i]);
		i++;
	}
}
