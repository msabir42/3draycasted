/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:32 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:34:22 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_keys(t_keys *keys)
{
	keys->a = 0;
	keys->w = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

void	init_game(t_game *game, t_data data, t_player p)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		exit(1);
	game->mlx.win = mlx_new_window(game->mlx.mlx, SCREEN_W, SCREEN_H, "cube3d");
	if (!game->mlx.win)
		exit(1);
	game->mlx.img = mlx_new_image(game->mlx.mlx, SCREEN_W, SCREEN_H);
	if (!game->mlx.img)
		exit(1);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
	game->data = data;
	game->player = p;
	init_keys(&game->keys);
}

void	clear_screen(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
