/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice_pixels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:50:00 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 19:24:43 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	clamp_texture_coordinate(int value, int max)
{
	if (value < 0)
		return (0);
	if (value >= max)
		return (max - 1);
	return (value);
}

static void	init_draw_data(t_draw_data *data, t_texture *tex, double wall_h)
{
	data->top = (SCREEN_H / 2) - (wall_h / 2);
	data->bottom = (SCREEN_H / 2) + (wall_h / 2);
	if (data->top < 0)
		data->top = 0;
	if (data->bottom > SCREEN_H)
		data->bottom = SCREEN_H;
	data->step = (double)tex->height / wall_h;
	if (data->step <= 0 || isnan(data->step) || isinf(data->step))
		data->step = 1.0;
	data->pos = (data->top - SCREEN_H / 2 + wall_h / 2) * data->step;
	if (data->pos < 0)
		data->pos = 0;
}

void	draw_slice_pixels(t_game *game, t_slice_param param)
{
	t_draw_data	data;
	int			y;
	int			tex_y;

	init_draw_data(&data, param.tex, param.wall_h);
	if (data.top >= data.bottom)
		return ;
	y = data.top;
	while (y < data.bottom)
	{
		tex_y = clamp_texture_coordinate((int)data.pos, param.tex->height);
		my_mlx_pixel_put(game, param.x, y, get_texture_color(param.tex,
				param.tex_x, tex_y));
		data.pos += data.step;
		y++;
	}
}
