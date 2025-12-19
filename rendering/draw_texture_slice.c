/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_slice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:21 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/19 19:59:22 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double	sanitize_wall_height(double h)
{
	if (h <= 0.1 || isnan(h) || isinf(h))
		return (SCREEN_H / 2);
	if (h > SCREEN_H * 10)
		return (SCREEN_H * 10);
	if (h < 1.0)
		return (1.0);
	return (h);
}

static t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->facing_right)
			return (&game->east_tex);
		return (&game->west_tex);
	}
	if (ray->facing_down)
		return (&game->south_tex);
	return (&game->north_tex);
}

static int	compute_tex_x(t_texture *tex, t_ray *ray, t_intersect hit)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = hit.hit_point_y - floor(hit.hit_point_y);
	else
		wall_x = hit.hit_point_x - floor(hit.hit_point_x);
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	prepare_slice_params(t_game *game, t_slice_param *param,
		t_intersect hit, t_ray *ray)
{
	param->tex = get_wall_texture(game, ray);
	if (!param->tex || !param->tex->img || !param->tex->addr)
		return ;
	if (param->tex->width <= 0 || param->tex->height <= 0)
		return ;
	param->tex_x = compute_tex_x(param->tex, ray, hit);
}

void	draw_textured_slice(t_game *game, int x, t_intersect hit, t_ray *ray)
{
	t_slice_param	param;
	double			wall_h;

	if (!game || !ray)
		return ;
	wall_h = (SCREEN_H / ray->dist);
	param.x = x;
	param.wall_h = sanitize_wall_height(wall_h);
	prepare_slice_params(game, &param, hit, ray);
	if (!param.tex || !param.tex->img || !param.tex->addr)
		return ;
	if (param.tex->width <= 0 || param.tex->height <= 0)
		return ;
	draw_slice_pixels(game, param);
}
