/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:50 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:30 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	find_map_start(char **lines, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (lines[i][j] && (lines[i][j] == ' ' || lines[i][j] == '\t'))
			j++;
		if (lines[i][j] && (lines[i][j] == '1' || lines[i][j] == '0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	process_lines(char **lines, int count, t_data *data)
{
	int	map_start;
	int	i;

	i = 0;
	map_start = find_map_start(lines, count);
	if (map_start == -1)
		return (print_error("No map found"), 0);
	while (i < map_start)
	{
		if (!is_empty_line(lines[i]))
		{
			if (!get_metadata(lines[i], data))
				return (0);
		}
		i++;
	}
	if (!validate_metadata(data))
		return (0);
	if (!parse_map_block(&lines[map_start], data))
		return (0);
	if (!validate_map(data))
		return (0);
	return (1);
}

int	fetch_lines(char *file, t_data *data)
{
	int		fd;
	char	**lines;
	int		count;
	int		result;

	if (!check_file(file, ".cub"))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file"), 0);
	if (!read_and_store_lines(fd, &lines, &count))
	{
		close(fd);
		return (print_error("Failed to read file"), 0);
	}
	close(fd);
	result = process_lines(lines, count, data);
	free_lines(lines, count);
	return (result);
}
