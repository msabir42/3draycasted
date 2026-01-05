/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:43 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/16 15:40:55 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	rotate_right(t_player *p)
{
	double	new_dirx;
	double	new_diry;
	double	new_planex;
	double	new_planey;

	new_dirx = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	new_diry = p->dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	new_planex = p->plane_x * cos(p->rot_speed) - p->plane_y
		* sin(p->rot_speed);
	new_planey = p->plane_x * sin(p->rot_speed) + p->plane_y
		* cos(p->rot_speed);
	p->dir_x = new_dirx;
	p->dir_y = new_diry;
	p->plane_x = new_planex;
	p->plane_y = new_planey;
}

void	rotate_left(t_player *p)
{
	double	new_dirx;
	double	new_diry;
	double	new_planex;
	double	new_planey;

	new_dirx = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	new_diry = p->dir_x * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
	new_planex = p->plane_x * cos(-p->rot_speed) - p->plane_y
		* sin(-p->rot_speed);
	new_planey = p->plane_x * sin(-p->rot_speed) + p->plane_y
		* cos(-p->rot_speed);
	p->dir_x = new_dirx;
	p->dir_y = new_diry;
	p->plane_x = new_planex;
	p->plane_y = new_planey;
}

int	is_movement_valid(t_game *game, double new_x, double new_y)
{
	double	offset;

	offset = 0.2;
	if (game->data.map[(int)(new_y + offset)][(int)(new_x + offset)] == 1)
		return (0);
	if (game->data.map[(int)(new_y + offset)][(int)(new_x - offset)] == 1)
		return (0);
	if (game->data.map[(int)(new_y - offset)][(int)(new_x - offset)] == 1)
		return (0);
	if (game->data.map[(int)(new_y - offset)][(int)(new_x + offset)] == 1)
		return (0);
	return (1);
}
