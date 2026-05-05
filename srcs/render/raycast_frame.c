/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:28:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/05 20:51:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "render3D.h"

// Calculates which vertical part of the screen must be filled by the wall.
// Raycasting renders the 3D one vertical column at a time. After the DDA
// finds a wall, we know how far the wall is from the player. This distance is
// then converted into a projected wall height.
// The projection formula is: wall height on screen = screen height / wall dist
// A close wall gives a small distance, producing a large column. A far wall
// gives a large distance, producing a small column.
// line_h stores the final height of the wall column in pixels to be drawn.
// draw_start and draw_end define the vertical pixel range where the wall will
// be drawn: draw_start is above the screen center; draw_end is below the screen
// center.
// Finally, the values are clamped to the screen limits so the renderer never
// writes pixels outside the image buffer.
void	ray_draw_range(t_game *g)
{
	int	col_height;

	col_height = (int)((double)g->win.height / g->ray.perp_wall_dist);
	if (col_height < 1)
		col_height = 1;
	g->ray.line_h = col_height;
	g->ray.draw_start = g->win.height / 2 - col_height / 2;
	g->ray.draw_end = g->win.height / 2 + col_height / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->win.height)
		g->ray.draw_end = g->win.height - 1;
}

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

// Initializes the DDA stepping direction and the first grid distances.
// The DDA algorithm needs to know two things before it starts:
// > In which direction the ray moves through the map:
//    - step_x = -1 means the ray moves left;
//    - step_x =  1 means the ray moves right;
//    - step_y = -1 means the ray moves upward;
//    - step_y =  1 means the ray moves downward.
// > How far the player is from the first grid boundary in each axis:
//    - side_dist_x is the distance to the first vertical grid line;
//    - side_dist_y is the distance to the first horizontal grid line.
// If the ray points left, the first vertical boundary is the left side of the
// current tile. If it points right, the first vertical boundary is the right
// side of the current tile.
// The same idea applies to Y:
// - upward rays use the top boundary of the tile;
// - downward rays use the bottom boundary of the tile.
// These initial distances decide the first DDA step. After that, ray_step()
// keeps adding delta_dist_x or delta_dist_y to move from boundary to boundary.
void	ray_init_steps(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->player.pos.tile_pos.x - g->ray.map_x)
			* g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + TILE_SIZE_3D
				- g->player.pos.tile_pos.x) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->player.pos.tile_pos.y - g->ray.map_y)
			* g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + TILE_SIZE_3D
				- g->player.pos.tile_pos.y) * g->ray.delta_dist_y;
	}
}

// Initializes all ray values needed to cast one screen column.
// Raycast renders the scene by launching one ray for each vertical column
// of the window. The column index is converted into camera space using cam_x.
// cam_x maps the screen column into the interval [-1, 1]:
// - -1 represents the far left side of the camera plane;
// -  0 represents the center of the screen;
// -  1 represents the far right side of the camera plane.
// The ray direction is calculated: player direction + camera plane * cam_x
// The player direction points forward. The camera plane is perpendicular to
// that direction and controls the field of view. Multiplying the plane by
// cam_x spreads the rays across the screen.

// map_x and map_y store the current map cell containing the player.
// The DDA algorithm starts from this cell and then walks through the grid until
// it finds a blocking tile.

// delta_dist_x and delta_dist_y represent how much distance must be added to
// the ray when it crosses one grid line in X or Y.
// If one ray direction component is zero, the ray will never cross grid lines
// in that axis. In that case, a very large value is used to avoid division by
// zero and to force the DDA to advance only through the other axis.
void	ray_init(t_game *g, int col)
{
	double	cam_x;

	cam_x = 2.0 * col / (double)g->win.width - 1.0;
	g->ray.camera_x = cam_x;
	g->ray.ray_dir_x = g->player.dir.x + g->player.plane.x * cam_x;
	g->ray.ray_dir_y = g->player.dir.y + g->player.plane.y * cam_x;
	g->ray.map_x = (int)g->player.pos.tile_pos.x;
	g->ray.map_y = (int)g->player.pos.tile_pos.y;
	g->ray.hit = 0;
	g->ray.hit_side = 0;
	g->ray.hit_tile = VOID;
	if (g->ray.ray_dir_x == 0.0)
		g->ray.delta_dist_x = 1e30;
	else
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (g->ray.ray_dir_y == 0.0)
		g->ray.delta_dist_y = 1e30;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
}

// Casts all rays needed to render one complete 3D frame.
// The screen is rendered column by column. For each column, the engine creates
// one ray with a slightly different direction, depending on the column position
// inside the camera plane.
//
// For each ray:
// > ray_init() prepares the ray direction and base values.
// > ray_init_steps() computes the initial DDA distances and step direction.
// > raycast_dda() walks through the map until a wall/gate is found.
// > ray_perp_wall_distance() computes the corrected wall distance.
// > ray_draw_range() converts that distance into screen coordinates.
// > render_wall_column() draws the textured wall slice.
//
// The perpendicular distance is also stored in z_buffer[col]. This buffer is
// later used when rendering sprites, so a sprite pixel is only drawn if it is
// closer than the wall already rendered in that column.
//
// center_hit stores information about the ray in the center of the screen.
// This can be used for interactions or detecting what the player
// is directly looking at.
void	raycast_frame(t_game *g)
{
	int	col;
	int	center_hit;

	if (!g)
		return ;
	col = -1;
	center_hit = 0;
	while (++col < g->win.width)
	{
		ray_init(g, col);
		ray_init_steps(g);
		if (raycast_find_wall(g))
		{
			ray_perp_wall_distance(g);
			ray_draw_range(g);
			render_wall_column(g, col);
			g->ray.z_buffer[col] = g->ray.perp_wall_dist;
			center_hit = register_center_hit(g, col, center_hit);
		}
	}
}
