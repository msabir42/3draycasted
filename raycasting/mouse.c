/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:42:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/24 18:28:59 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_speed;

	if (!game->mouse.enabled)
		return (0);
	game->mouse.x = x;
	game->mouse.y = y;
	delta_x = x - game->mouse.last_x;
	rotation_speed = 0.002;
	if (delta_x > 0)
		rotate_right(&game->player);
	else if (delta_x < 0)
		rotate_left(&game->player);
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, SCREEN_W / 2, SCREEN_H / 2);
	game->mouse.last_x = SCREEN_W / 2;
	return (0);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		game->mouse.enabled = !game->mouse.enabled;
		if (game->mouse.enabled)
		{
			mlx_mouse_hide(game->mlx.mlx, game->mlx.win);
			mlx_mouse_move(game->mlx.mlx, game->mlx.win, SCREEN_W / 2, SCREEN_H
				/ 2);
		}
		else
		{
			mlx_mouse_show(game->mlx.mlx, game->mlx.win);
		}
	}
	return (0);
}

void	handle_mouse_rotation(t_game *game)
{
	(void)game;
}
