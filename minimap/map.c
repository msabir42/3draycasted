/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:35:26 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 17:37:57 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_TILE)
	{
		j = 0;
		while (j < MINI_TILE)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < game->data.map_height)
	{
		j = 0;
		while (j < game->data.map_width)
		{
			if (game->data.map[i][j] == 1)
				color = 0xFFFFFF;
			else
				color = 0x454545;
			draw_tile(game, j * MINI_TILE + OFFSET,
				i * MINI_TILE + OFFSET, color);
			j++;
		}
		i++;
	}
}

void	cast_single_ray_minimap(t_game *game, double ray_angle)
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
		draw_line_map(game, &game->player, final_hit, 0xFF0000);
	}
}

void	cast_all_rays_minimap(t_game *game)
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
		cast_single_ray_minimap(game, ray_angle);
		i++;
	}
}

void	minimap(t_game *game)
{
	draw_map(game);
	draw_player(&game->player, game);
	cast_all_rays_minimap(game);
}
