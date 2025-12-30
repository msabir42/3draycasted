/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:50 by msabir            #+#    #+#             */
/*   Updated: 2025/12/30 01:06:06 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_map(char *line, t_data *data, t_parse_state *state)
{
	if (state->row >= MAP_HEIGHT)
		return (print_error("Map is too tall"), 0);
	if (is_empty_line(line))
		return (1);
	if (!parse_map_line(line, data, state->row))
		return (0);
	state->row++;
	return (1);
}

static int	process_line(char *line, t_data *data, t_parse_state *state)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (tmp)
		*tmp = '\0';
	if (is_empty_line(line))
		return (1);
	if (is_map_line(line))
	{
		state->map_started = 1;
		return (handle_map(line, data, state));
	}
	if (!state->map_started)
		return (get_metadata(line, data));
	return (print_error("Invalid content after map started"), 0);
}

static int	read_file_lines(int fd, t_data *data, t_parse_state *state)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, data, state))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	fetch_lines(char *file, t_data *data)
{
	int				fd;
	t_parse_state	state;

	if (!check_file(file, ".cub"))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file"), 0);
	state.map_started = 0;
	state.row = 0;
	if (!read_file_lines(fd, data, &state))
	{
		close(fd);
		return (0);
	}
	close(fd);
	data->map_height = state.row;
	if (!validate_metadata(data) || !validate_map(data))
		return (0);
	return (1);
}
