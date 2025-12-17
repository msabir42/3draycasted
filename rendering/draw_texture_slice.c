/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_slice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:21 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/17 19:09:40 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_textured_slice(t_game *game, int x, double wall_height,
		t_intersect hit, t_ray *ray)
{
	int wall_top;
	int wall_bottom;
	int y;
	double step;
	double tex_pos;
	int tex_y;
	int tex_x;
	int color;
	t_texture *texture;
	double wall_x;

	if (wall_height <= 0.1 || isnan(wall_height) || isinf(wall_height))
		wall_height = SCREEN_H / 2;
	if (wall_height > SCREEN_H * 10)
		wall_height = SCREEN_H * 10;
	if (ray->side == 0)
	{
		texture = ray->facing_right ? &game->east_tex : &game->west_tex;
		wall_x = hit.hit_point_y - floor(hit.hit_point_y);
		tex_x = (int)(wall_x * texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
	}
	else
	{
		texture = ray->facing_down ? &game->south_tex : &game->north_tex;
		wall_x = hit.hit_point_x - floor(hit.hit_point_x);
		tex_x = (int)(wall_x * texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
	}
	if (!texture || !texture->img || !texture->addr || texture->width <= 0
		|| texture->height <= 0)
	{
		/* Silent fail: texture missing */
		return ;
	}
	wall_top = (SCREEN_H / 2) - (wall_height / 2);
	wall_bottom = (SCREEN_H / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > SCREEN_H)
		wall_bottom = SCREEN_H;
	if (wall_top >= wall_bottom)
		return ;
	if (wall_height < 1.0)
		wall_height = 1.0;
	step = (double)texture->height / wall_height;
	if (isnan(step) || isinf(step) || step <= 0)
		step = 1.0;
	tex_pos = (wall_top - SCREEN_H / 2 + wall_height / 2) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = wall_top;
	while (y < wall_bottom)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(game, x, y, color);
		tex_pos += step;
		y++;
	}
}
