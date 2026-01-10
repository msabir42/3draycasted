/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_helper_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 22:53:23 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	check_map_bounds(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->data.map_width
		|| map_y < 0 || map_y >= game->data.map_height)
		return (0);
	return (1);
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
		if (!check_map_bounds(game, map_x, map_y))
			break ;
		if (game->data.map[map_y][map_x] == '1')
		{
			set_values(intersect, x_next, y_next, ray);
			break ;
		}
		else
			increment_values(&x_next, &y_next, intersect);
	}
}
