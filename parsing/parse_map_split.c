/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:30 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_player_found(t_data *data, int y, int x)
{
	if (data->player_found)
	{
		print_error("Multiple player positions found");
		return (0);
	}
	data->player_start_x = x;
	data->player_start_y = y;
	data->player_start_direction = data->map[y][x];
	data->player_found = 1;
	data->map[y][x] = '0';
	return (1);
}

int	validate_map_chars(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!is_map_char(data->map[y][x]))
			{
				print_error("Invalid character in map");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	find_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (is_player_char(data->map[y][x]))
			{
				if (!handle_player_found(data, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
