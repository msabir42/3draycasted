/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:42:02 by msabir            #+#    #+#             */
/*   Updated: 2026/01/04 20:01:58 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rotate_mouse_right(t_player *p)
{
	double	new_dirx;
	double	new_diry;
	double	new_planex;
	double	new_planey;

	new_dirx = p->dir_x * cos(MOUSE_SPEED) - p->dir_y * sin(MOUSE_SPEED);
	new_diry = p->dir_x * sin(MOUSE_SPEED) + p->dir_y * cos(MOUSE_SPEED);
	new_planex = p->plane_x * cos(MOUSE_SPEED) - p->plane_y
		* sin(MOUSE_SPEED);
	new_planey = p->plane_x * sin(MOUSE_SPEED) + p->plane_y
		* cos(MOUSE_SPEED);
	p->dir_x = new_dirx;
	p->dir_y = new_diry;
	p->plane_x = new_planex;
	p->plane_y = new_planey;
}

void	rotate_mouse_left(t_player *p)
{
	double	new_dirx;
	double	new_diry;
	double	new_planex;
	double	new_planey;

	new_dirx = p->dir_x * cos(-MOUSE_SPEED) - p->dir_y * sin(-MOUSE_SPEED);
	new_diry = p->dir_x * sin(-MOUSE_SPEED) + p->dir_y * cos(-MOUSE_SPEED);
	new_planex = p->plane_x * cos(-MOUSE_SPEED) - p->plane_y
		* sin(-MOUSE_SPEED);
	new_planey = p->plane_x * sin(-MOUSE_SPEED) + p->plane_y
		* cos(-MOUSE_SPEED);
	p->dir_x = new_dirx;
	p->dir_y = new_diry;
	p->plane_x = new_planex;
	p->plane_y = new_planey;
}

int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_speed;

	if (!game->mouse.enabled)
		return (0);
	game->mouse.x = x;
	game->mouse.y = y;
	delta_x = x - game->mouse.last_x;
	rotation_speed = 0.001;
	if (delta_x > 0)
		rotate_mouse_right(&game->player);
	else if (delta_x < 0)
		rotate_mouse_left(&game->player);
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
