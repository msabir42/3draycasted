/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:31 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_bounds(t_game *game, int check_y, int check_x)
{
	if (check_y < 0 || check_y >= game->data.map_height
		|| check_x < 0 || check_x >= game->data.map_width
		|| game->data.map[check_y][check_x] == '1')
		return (0);
	return (1);
}

int	is_movement_valid(t_game *game, double new_x, double new_y)
{
	double	offset;
	int		check_y;
	int		check_x;

	offset = 0.2;
	check_y = (int)(new_y + offset);
	check_x = (int)(new_x + offset);
	if (!check_bounds(game, check_y, check_x))
		return (0);
	check_x = (int)(new_x - offset);
	if (!check_bounds(game, check_y, check_x))
		return (0);
	check_y = (int)(new_y - offset);
	check_x = (int)(new_x - offset);
	if (!check_bounds(game, check_y, check_x))
		return (0);
	check_x = (int)(new_x + offset);
	if (!check_bounds(game, check_y, check_x))
		return (0);
	return (1);
}
