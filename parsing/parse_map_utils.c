/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:58 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:29:09 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	set_player(t_data *data, int row, int col, char c)
{
	if (data->player_found)
		return (print_error("Multiple player starting positions\n"), 0);
	data->player_start_x = col;
	data->player_start_y = row;
	data->player_start_direction = c;
	data->player_found = 1;
	data->map[row][col] = 0;
	return (1);
}

static int	set_cell(t_data *data, int row, int col, char c)
{
	if (c == ' ')
		data->map[row][col] = 0;
	else if (c == '0')
		data->map[row][col] = 0;
	else if (c == '1')
		data->map[row][col] = 1;
	else if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
	{
		if (!set_player(data, row, col, c))
			return (0);
	}
	else if (c != '\t' && c != '\n' && c != '\r'
		&& c != '\v' && c != '\f')
		return (print_error("Invalid character in map\n"), 0);
	return (1);
}

int	parse_map_line(char *line, t_data *data, int row)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (line[i] && col < MAP_WIDTH)
	{
		if (!set_cell(data, row, col, line[i]))
			return (0);
		if (line[i] == ' ' || line[i] == '0'
			|| line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			col++;
		i++;
	}
	if (col > data->map_width)
		data->map_width = col;
	while (col < MAP_WIDTH)
	{
		data->map[row][col] = 1;
		col++;
	}
	return (1);
}
