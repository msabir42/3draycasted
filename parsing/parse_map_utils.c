/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:58 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:25 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	set_player(t_data *data, int row, int col, char c)
{
	if (data->player_found)
		return (print_error("Multiple player starting positions"), 0);
	data->player_start_x = col;
	data->player_start_y = row;
	data->player_start_direction = c;
	data->player_found = 1;
	data->map[row][col] = 0;
	return (1);
}

static int	set_cell(t_data *data, int row, int col, char c)
{
	if (c == '0')
		data->map[row][col] = 0;
	else if (c == '1')
		data->map[row][col] = 1;
	else if (c == ' ' || c == '\t')
		data->map[row][col] = 2;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!set_player(data, row, col, c))
			return (0);
	}
	else
		return (print_error("Invalid character in map"), 0);
	return (1);
}

static int	find_line_end(char *line, int start)
{
	int	end;

	end = start;
	while (line[end] && line[end] != '\n' && line[end] != '\r')
		end++;
	return (end);
}

int	pad_row_with_walls(t_data *data, int row, int col);

static int	scan_row_chars(char *line, t_data *data, int row,
			int start)
{
	int	end;
	int	i;
	int	col;

	end = find_line_end(line, start);
	i = start;
	col = 0;
	while (i < end && col < MAP_WIDTH)
	{
		if (!set_cell(data, row, col, line[i]))
			return (0);
		col++;
		i++;
	}
	if (col > data->map_width)
		data->map_width = col;
	data->row_lengths[row] = col;
	while (col < MAP_WIDTH)
	{
		data->map[row][col] = 2;
		col++;
	}
	return (1);
}

int	parse_map_line(char *line, t_data *data, int row)
{
	if (!scan_row_chars(line, data, row, 0))
		return (0);
	return (1);
}
