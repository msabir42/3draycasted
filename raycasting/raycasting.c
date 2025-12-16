/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:54 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 17:06:09 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	distance(double x1, double x2, double y1, double y2)
{
	double	dst;

	dst = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (dst);
}

t_intersect	calculate_distance(t_game *game, t_player *p, t_ray *ray)
{
	t_intersect	horiz;
	t_intersect	vertic;

	ray_horizontal_intersection(p, ray, &horiz);
	ray_vertical_intersection(p, ray, &vertic);
	find_hit_point(ray, game, &horiz);
	find_hit_point(ray, game, &vertic);
	horiz.dist = 1e30;
	vertic.dist = 1e30;
	check_horiz_vertic(&horiz, &vertic, p, ray);
	if (horiz.dist < vertic.dist)
	{
		ray->dist = horiz.dist;
		ray->side = 1;
		return (horiz);
	}
	else
	{
		ray->dist = vertic.dist;
		ray->side = 0;
		return (vertic);
	}
}

void	draw_line(t_game *game, t_player *p, t_intersect Hit, int color)
{
	t_coordinates	coord;
	int				i;

	i = 0;
	coord.dx = (Hit.hit_point_x - p->pos_x) * TILE_SIZE;
	coord.dy = (Hit.hit_point_y - p->pos_y) * TILE_SIZE;
	coord.steps = (int)fmax(fabs(coord.dx), fabs(coord.dy));
	if (coord.steps == 0)
		return ;
	coord.x_inc = coord.dx / coord.steps;
	coord.y_inc = coord.dy / coord.steps;
	coord.x = p->pos_x * TILE_SIZE;
	coord.y = p->pos_y * TILE_SIZE;
	while (i <= coord.steps)
	{
		coord.px = (int)coord.x;
		coord.py = (int)coord.y;
		if (coord.px >= 0 || coord.px < SCREEN_W
			|| coord.py >= 0 || coord.py < SCREEN_H)
			my_mlx_pixel_put(game, coord.px, coord.py, color);
		coord.x += coord.x_inc;
		coord.y += coord.y_inc;
		i++;
	}
}

void	cast_single_ray(t_game *game, double ray_angle)
{
	t_ray		ray;
	t_intersect	final_hit;

	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	ray.angle = ray_angle;
	ray.found_wall = false;
	ray_direction(&ray);
	final_hit = calculate_distance(game, &game->player, &ray);
	if (ray.found_wall)
	{
		draw_line(game, &game->player, final_hit, 0xFF0000);
	}
}

void	cast_all_rays(t_game *game)
{
	double	ray_angle;
	double	angle_step;
	double	player_angle;
	double	start_angle;
	int		i;

	i = 0;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	ray_angle = 0;
	start_angle = player_angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + (i * angle_step);
		cast_single_ray(game, ray_angle);
		i++;
	}
}
