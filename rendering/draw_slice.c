/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:12 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/19 19:14:49 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

static double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

static double	fix_fisheye(t_game *game, double ray_angle, double dist)
{
	double	player_angle;
	double	angle_diff;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	angle_diff = player_angle - ray_angle;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	return (dist * cos(angle_diff));
}

static double	sanitize_ray_distance(double dist)
{
	if (dist < 0.05)
		return (0.05);
	if (dist > 100)
		return (100);
	if (isnan(dist) || isinf(dist))
		return (1.0);
	return (dist);
}

void	draw_slice_to_screen(t_game *game, double ray_angle, int x)
{
	t_ray		ray;
	t_intersect	hit;
	double		wall_height;

	ray_angle = normalize_angle(ray_angle);
	ray.angle = ray_angle;
	ray.found_wall = false;
	ray_direction(&ray);
	hit = calculate_distance(game, &game->player, &ray);
	ray.dist = sanitize_ray_distance(ray.dist);
	ray.dist = fix_fisheye(game, ray_angle, ray.dist);
	if (ray.found_wall)
	{
		wall_height = wall_projection_height(&ray);
		draw_textured_slice(game, x, wall_height, hit, &ray);
	}
}
