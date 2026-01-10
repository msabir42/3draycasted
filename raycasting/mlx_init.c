/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:32 by oukadir           #+#    #+#             */
/*   Updated: 2026/01/10 17:19:36 by msabir           ###   ########.fr       */
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

int	close_game(t_game *game)
{
	free_textures(game);
	cleanup_data(&game->data);
	if (game->mlx.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	free(game);
	exit(0);
	return (0);
}

void	mlx_calls(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx.mlx, game_loop, game);
	draw_background(game, game->data.ceiling_color, game->data.floor_color);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	mlx_loop(game->mlx.mlx);
}
