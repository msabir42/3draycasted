/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 03:59:59 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:24 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_invalid(char c)
{
	return (c == ' ' || c == '\0');
}

static int	check_cell_enclosed(t_data *data, int x, int y)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (x <= 0 || y <= 0 || x >= data->map_width - 1
		|| y >= data->map_height - 1)
		return (0);
	up = data->map[y - 1][x];
	down = data->map[y + 1][x];
	left = data->map[y][x - 1];
	right = data->map[y][x + 1];
	if (is_invalid(up) || is_invalid(down) || is_invalid(left)
		|| is_invalid(right))
		return (0);
	return (1);
}

static int	validate_map_closed(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (is_walkable(data->map[y][x]))
			{
				if (!check_cell_enclosed(data, x, y))
				{
					print_error("Map is not closed");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_walls(t_data *data)
{
	if (!validate_map_closed(data))
		return (0);
	return (1);
}
