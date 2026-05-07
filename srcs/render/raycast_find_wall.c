/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_find_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:39:40 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/07 15:45:32 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "render3D.h"

// Computes the perpendicular distance from the player to the wall hit.
// During the DDA loop, side_dist_x and side_dist_y are increased before the
// tile collision is checked, 'cause of that, when a wall is found, the side
// distance has already moved one delta too far.
// To recover the real hit distance: we subtract delta_dist_x if the last step
// was on the X axis; or subtract delta_dist_y if the last step was on the Y 
// axis.
// This distance is called "perpendicular" 'cause it represents the distance
// from the player to the camera plane.
// Using perpendicular distance is essential to avoid the fish-eye effect.
// Without it, rays cast near the sides of the screen would appear longer than
// center rays, causing straight walls to look curved.
// The minimum value protects the projection formula from division by zero.
// Without this guard, a wall extremely close to the player could produce an
// invalid or infinitely tall wall column.
void	ray_perp_wall_distance(t_game *g)
{
	if (g->ray.hit_side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	if (g->ray.perp_wall_dist < 1e-6)
		g->ray.perp_wall_dist = 1e-6;
}

// Advances the ray to the next map cell using one step of the DDA algorithm.
// side_dist_x stores the distance from the player to the next vertical grid
// line. side_dist_y stores the distance from the player to the next horizontal
// grid line.
// If side_dist_x is smaller, the ray reaches a vertical grid line first, so
// the algorithm advances one tile on the X axis. Otherwise, it advances one
// tile on the Y axis.
// hit_side is saved because it tells the renderer which kind of wall was hit:
// 0 means the ray crossed an X boundary, so the wall is an east/west wall;
// 1 means the ray crossed a Y boundary, so the wall is a north/south wall.
static void	advance_ray_step(t_game *g)
{
	if (g->ray.side_dist_x < g->ray.side_dist_y)
	{
		g->ray.side_dist_x += g->ray.delta_dist_x;
		g->ray.map_x += g->ray.step_x;
		g->ray.hit_side = 0;
	}
	else
	{
		g->ray.side_dist_y += g->ray.delta_dist_y;
		g->ray.map_y += g->ray.step_y;
		g->ray.hit_side = 1;
	}
}

// Checks whether the ray is still inside a valid map area after moving.
// This function implements horizontal wrapping, used for Pac-Man style.
// A normal raycaster would stop when the ray leaves the map bounds.
// Some rows can connect the left and right edges of the map.
// If the current row supports wrapping: when the ray exits before column 0,
// it is moved to the last valid column; when the ray exits after the last 
// column, it is moved back to column 0.
// If the row does not support wrapping, the function only accepts positions
// between column 0 and the last valid column of that row.
// This is important because map rows may have different lengths, especially
// if the map is parsed with irregular line sizes.
// Return 1 means the ray position is valid and DDA can continue ;
// Return 0 means the ray left the playable/map area and DDA should stop.
static int	handle_ray_horizontal_wrap(t_game *g)
{
	int	last;

	if (!g || g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
		return (0);
	last = map_row_last_col(g, g->ray.map_y, 1);
	if (last >= 0)
	{
		if (g->ray.map_x < 0)
			g->ray.map_x = last;
		else if (g->ray.map_x > last)
			g->ray.map_x = 0;
		return (1);
	}
	last = map_row_last_col(g, g->ray.map_y, 0);
	if (last < 0 || g->ray.map_x < 0 || g->ray.map_x > last)
		return (0);
	return (1);
}

// Runs the DDA loop for the current ray until a blocking tile is hit.
// The ray starts in the player's current map cell. On each loop iteration,
// advance_ray_step() moves it to the next cell crossed by the ray direction.
// After each step, the position is validated. This protects the raycaster from
// reading outside the map array and also applies horizontal wrapping when the
// ray crosses a tunnel row.
// The ray stops if the tile blocks vision.
// A closed gate: GATE blocks the ray only when gate_passable == 0.
// A solid map tile: any tile classified as TILE_SOLID blocks the ray.
// When a blocking tile is found, the tile type is saved in hit_tile so the
// renderer can choose the correct texture.
// The loop limit prevents infinite ray traversal.
// Returns 1 if the ray hit a blocking tile;
// Returns 0 if the ray stopped without finding a valid wall hit.
int	raycast_find_wall(t_game *g)
{
	int		i;
	int		limit;
	int		hit;
	char	tile;

	i = -1;
	limit = g->map.width * g->map.height + 50;
	hit = 0;
	while (++i < limit)
	{
		advance_ray_step(g);
		if (!handle_ray_horizontal_wrap(g))
			break ;
		tile = map_get_tile(g, g->ray.map_y, g->ray.map_x);
		if ((tile == GATE && g->gate_passable == 0) || (tile != GATE
				&& map_tile_type(tile, TILE_SOLID)))
		{
			g->ray.hit_tile = tile;
			hit = 1;
			break ;
		}
	}
	return (hit);
}
