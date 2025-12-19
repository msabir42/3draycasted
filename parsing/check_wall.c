/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:47 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:53:16 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_horizontal_walls(t_data *data)
{
	int	x;

	x = 0;
	while (x < MAP_WIDTH)
	{
		if (data->map[0][x] != 1)
			return (print_error("Top border not completely closed"), 0);
		if (data->map[MAP_HEIGHT - 1][x] != 1)
			return (print_error("Bottom border not completely closed"), 0);
		x++;
	}
	return (1);
}

static int	check_vertical_walls(t_data *data)
{
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		if (data->map[y][0] != 1)
			return (print_error("Left border not completely closed"), 0);
		if (data->map[y][MAP_WIDTH - 1] != 1)
			return (print_error("Right border not completely closed"), 0);
		y++;
	}
	return (1);
}

int	check_closed_walls(t_data *data)
{
	if (!check_horizontal_walls(data))
		return (0);
	if (!check_vertical_walls(data))
		return (0);
	return (1);
}
