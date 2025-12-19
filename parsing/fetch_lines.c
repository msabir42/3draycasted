/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:50 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:25:18 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	g_meta_done;
static int	g_map_started;
static int	g_row;

int	check_file(char *file, char *ext)
{
	int	fd;
	int	len;

	if (!file || !ext)
		return (0);
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ext, 4) != 0)
		return (print_error("Invalid extension\n"), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("File cant be open\n"), 0);
	close(fd);
	return (1);
}

static int	handle_map(char *line, t_data *data)
{
	if (g_row >= MAP_HEIGHT)
		return (print_error("Map is too tall\n"), 0);
	if (!parse_map_line(line, data, g_row))
		return (0);
	g_row++;
	return (1);
}

static int	handle_metadata(char *line, t_data *data)
{
	if (!get_metadata(line, data))
		return (0);
	if (data->north_texture_path && data->south_texture_path
		&& data->west_texture_path && data->east_texture_path
		&& data->ceiling_color != -1 && data->floor_color != -1)
		g_meta_done = 1;
	return (1);
}

static int	process_line(char *line, t_data *data)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (tmp)
		*tmp = '\0';
	if (is_empty_line(line))
		return (1);
	if (!g_meta_done && !g_map_started)
		return (handle_metadata(line, data));
	if (is_map_line(line))
	{
		g_map_started = 1;
		return (handle_map(line, data));
	}
	return (g_meta_done);
}

int	fetch_lines(char *file, t_data *data)
{
	int		fd;
	char	*line;

	if (!check_file(file, ".cub"))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file\n"), 0);
	g_meta_done = 0;
	g_map_started = 0;
	g_row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, data))
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data->map_height = g_row;
	if (!validate_metadata(data) || !validate_map(data))
		return (0);
	return (1);
}
