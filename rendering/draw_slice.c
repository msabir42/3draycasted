#include "../include/cub3d.h"
#include <math.h>
#include <stdio.h>

void	draw_slice_to_screen(t_game *game, double ray_angle, int x)
{
	t_ray ray;
	t_intersect final_hit;
	double wall_height;
	double player_angle;
	double angle_diff;

	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	ray.angle = ray_angle;
	ray.found_wall = false;
	ray_direction(&ray);
	final_hit = calculate_distance(game, &game->player, &ray);
	angle_diff = player_angle - ray_angle;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	if (ray.dist < 0.05)
		ray.dist = 0.05;
	if (ray.dist > 100)
		ray.dist = 100;
	if (isnan(ray.dist) || isinf(ray.dist))
		ray.dist = 1.0;
	ray.dist *= cos(angle_diff);
	if (ray.dist < 0.05)
		ray.dist = 0.05;
	if (ray.found_wall)
	{
		wall_height = wall_projection_height(&ray);
		draw_textured_slice(game, x, wall_height, final_hit, &ray);
	}
	else
	{
		/* no wall found for this ray */
	}
}