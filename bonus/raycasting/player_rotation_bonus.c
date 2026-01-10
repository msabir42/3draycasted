/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:32:43 by oukadir           #+#    #+#             */
/*   Updated: 2026/01/10 22:53:23 by msabir           ###   ########.fr       */
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
