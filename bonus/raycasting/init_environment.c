/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:05 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:33:41 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;

	pixel = game->mlx.addr + (y * game->mlx.line_len + x * (game->mlx.bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_background(t_game *game, int ceiling_color, int floor_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H / 2)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_player *p, t_game *game)
{
	int	i;
	int	j;
	int	pos_x;
	int	pos_y;

	i = -2;
	pos_x = p->pos_x * MINI_TILE + OFFSET;
	pos_y = p->pos_y * MINI_TILE + OFFSET;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
				my_mlx_pixel_put(game, pos_x + i, pos_y + j, 0xFFFF00);
			j++;
		}
		i++;
	}
}
