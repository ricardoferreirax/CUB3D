#include "../Pac_Struct.h"

static int	get_front_tile_coord(t_game *g, int *map_x, int *map_y)
{
	double	front_x;
	double	front_y;

	if (!g || !map_x || !map_y)
		return (0);
	front_x = g->player.pos_x + g->player.dir_x * 0.60;
	front_y = g->player.pos_y + g->player.dir_y * 0.60;
	*map_x = (int)front_x;
	*map_y = (int)front_y;
	if (*map_x < 0 || *map_x >= g->map.width)
		return (0);
	if (*map_y < 0 || *map_y >= g->map.height)
		return (0);
	return (1);
}

void	handle_gate_toggle(t_game *g)
{
	int	map_x;
	int	map_y;

	if (!g || !g->key.e || g->key.e_lock)
		return ;
	g->key.e_lock = 1;
	if (!get_front_tile_coord(g, &map_x, &map_y))
		return ;
	if (map_get_tile(g, map_y, map_x) == GATE)
		g->gate_passable = !g->gate_passable;
}
