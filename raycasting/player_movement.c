/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:37 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:37:59 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
	if (is_movement_valid(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
	{
		if (is_movement_valid(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (is_movement_valid(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
	if (is_movement_valid(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
	{
		if (is_movement_valid(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (is_movement_valid(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
	if (is_movement_valid(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
	{
		if (is_movement_valid(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (is_movement_valid(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

void	move_down(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.dir_y * game->player.move_speed;
	if (is_movement_valid(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
	{
		if (is_movement_valid(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (is_movement_valid(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 13 || keycode == 119)
		game->keys.w = 1;
	if (keycode == 1 || keycode == 115)
		game->keys.s = 1;
	if (keycode == 0 || keycode == 97)
		game->keys.a = 1;
	if (keycode == 2 || keycode == 100)
		game->keys.d = 1;
	if (keycode == 113 || keycode == 65361)
		game->keys.left = 1;
	if (keycode == 101 || keycode == 65363)
		game->keys.right = 1;
	if (keycode == 65307)
		game->keys.esc = 1;
	return (0);
}
