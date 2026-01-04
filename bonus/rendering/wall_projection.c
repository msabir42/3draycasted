/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:39 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/19 19:12:58 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	wall_projection_height(t_ray *ray)
{
	double	projection_height;
	double	dist_to_projection_plane;

	dist_to_projection_plane = (SCREEN_W / 2) / tan(FOV / 2);
	if (ray->dist < 0.05)
		ray->dist = 0.05;
	if (ray->dist > 100)
		ray->dist = 100;
	if (isnan(ray->dist) || isinf(ray->dist))
		ray->dist = 1.0;
	projection_height = (0.5 * dist_to_projection_plane) / ray->dist;
	if (projection_height > SCREEN_H * 10)
		projection_height = SCREEN_H * 10;
	if (projection_height < 1)
		projection_height = 1.0;
	if (isnan(projection_height) || isinf(projection_height))
		projection_height = SCREEN_H / 2;
	return (projection_height);
}
