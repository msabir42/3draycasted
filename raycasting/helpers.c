/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:53:04 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 17:35:07 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_values(t_intersect *intersect, double x_next,
		double y_next, t_ray *ray)
{
	intersect->hit_point_x = x_next;
	intersect->hit_point_y = y_next;
	intersect->found = true;
	ray->found_wall = true;
}

void	increment_values(double *x_next, double *y_next, t_intersect *intersect)
{
	*x_next += intersect->x_step;
	*y_next += intersect->y_step;
}

void	check_horiz_vertic(t_intersect *horiz, t_intersect *vertic,
		t_player *p, t_ray *ray)
{
	if (horiz->found)
		horiz->dist = distance(p->pos_x, horiz->hit_point_x, p->pos_y,
				horiz->hit_point_y);
	if (vertic->found)
		vertic->dist = distance(p->pos_x, vertic->hit_point_x, p->pos_y,
				vertic->hit_point_y);
	if (horiz->found || vertic->found)
		ray->found_wall = true;
}

void	draw_line_map(t_game *game, t_player *p, t_intersect Hit, int color)
{
	t_coordinates	coord;
	int				i;

	i = 0;
	coord.dx = (Hit.hit_point_x - p->pos_x) * MINI_TILE;
	coord.dy = (Hit.hit_point_y - p->pos_y) * MINI_TILE;
	coord.steps = (int)fmax(fabs(coord.dx), fabs(coord.dy));
	if (coord.steps == 0)
		return ;
	coord.x_inc = coord.dx / coord.steps;
	coord.y_inc = coord.dy / coord.steps;
	coord.x = p->pos_x * MINI_TILE + OFFSET;
	coord.y = p->pos_y * MINI_TILE + OFFSET;
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
