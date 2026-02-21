#include "../Pac_Struct.h"

static int	gate_front(t_game *g, int *mx, int *my)
{
	double	fx;
	double	fy;

	if (!g || !mx || !my)
		return (0);
	fx = g->player.pos_x + g->player.dir_x * 0.60;
	fy = g->player.pos_y + g->player.dir_y * 0.60;
	*mx = (int)fx;
	*my = (int)fy;
	if (*mx < 0 || *mx >= g->map.width)
		return (0);
	if (*my < 0 || *my >= g->map.height)
		return (0);
	return (1);
}

static void	gate_toggle_front(t_game *g)
{
	int		mx;
	int		my;
	char	t;

	if (!gate_front(g, &mx, &my))
		return ;
	t = map_get_tile(g, my, mx);
	if (t != GATE)
		return ;
	if (g->gate_passable)
		g->gate_passable = 0;
	else
		g->gate_passable = 1;
}

void	handle_gate_input(t_game *g)
{
	if (!g)
		return ;
	if (!g->key.e)
		return ;
	if (g->key.e_lock)
		return ;
	g->key.e_lock = 1;
	gate_toggle_front(g);
}
