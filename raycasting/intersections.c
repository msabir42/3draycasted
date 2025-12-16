/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:26 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:54:02 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_direction(t_ray *ray)
{
	ray->facing_down = ray->angle > 0 && ray->angle < M_PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
	ray->facing_left = !ray->facing_right;
}

void	ray_horizontal_intersection(t_player *p, t_ray *ray, t_intersect *inter)
{
	inter->found = false;
	if (ray->angle == 0 || ray->angle == M_PI)
		return ;
	inter->y_intersect = floor(p->pos_y);
	if (ray->facing_down)
		inter->y_intersect += 1;
	inter->x_intersect = p->pos_x + (inter->y_intersect - p->pos_y)
		/ tan(ray->angle);
	if (ray->facing_down)
		inter->y_step = 1;
	else
		inter->y_step = -1;
	inter->x_step = inter->y_step / tan(ray->angle);
}

void	ray_vertical_intersection(t_player *p, t_ray *ray, t_intersect *inter)
{
	inter->found = false;
	if (ray->angle == 0.5 * M_PI || ray->angle == 1.5 * M_PI)
		return ;
	inter->x_intersect = floor(p->pos_x);
	if (ray->facing_right)
		inter->x_intersect += 1;
	inter->y_intersect = p->pos_y + (inter->x_intersect - p->pos_x)
		* tan(ray->angle);
	if (ray->facing_right)
		inter->x_step = 1;
	else
		inter->x_step = -1;
	inter->y_step = inter->x_step * tan(ray->angle);
}

void	find_hit_point(t_ray *ray, t_game *game, t_intersect *intersect)
{
	double	x_next;
	double	y_next;
	int		map_x;
	int		map_y;

	x_next = intersect->x_intersect;
	y_next = intersect->y_intersect;
	while (1)
	{
		map_x = (int)x_next;
		if (ray->facing_left && map_x == x_next)
			map_x--;
		map_y = (int)(y_next);
		if (ray->facing_up && map_y == y_next)
			map_y--;
		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			break ;
		if (game->data.map[map_y][map_x] == 1)
		{
			set_values(intersect, x_next, y_next, ray);
			break ;
		}
		else
			increment_values(&x_next, &y_next, intersect);
	}
}
