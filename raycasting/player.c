/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:49 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:36:16 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_north_south(t_player *p, t_data *data)
{
	if (data->player_start_direction == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (data->player_start_direction == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

void	init_west_east(t_player *p, t_data *data)
{
	if (data->player_start_direction == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (data->player_start_direction == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_player *p, t_data *data)
{
	p->pos_x = data->player_start_x + 0.5;
	p->pos_y = data->player_start_y + 0.5;
	init_north_south(p, data);
	init_west_east(p, data);
	p->move_speed = 0.005;
	p->rot_speed = 0.003;
	p->angle = M_PI / 4;
}

int	key_release(int keycode, t_game *game)
{
	if ((keycode == 13 || keycode == 119))
		game->keys.w = 0;
	else if ((keycode == 1 || keycode == 115))
		game->keys.s = 0;
	else if ((keycode == 0 || keycode == 97))
		game->keys.a = 0;
	else if ((keycode == 2 || keycode == 100))
		game->keys.d = 0;
	else if ((keycode == 113 || keycode == 65361))
		game->keys.left = 0;
	else if ((keycode == 101 || keycode == 65363))
		game->keys.right = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	if (game->keys.esc)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		exit(0);
	}
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_down(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(&game->player);
	if (game->keys.right)
		rotate_right(&game->player);
	clear_screen(game);
	draw_background(game, game->data.ceiling_color, game->data.floor_color);
	draw_walls(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}
