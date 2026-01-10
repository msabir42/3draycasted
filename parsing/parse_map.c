/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:02 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:29 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**create_map_grid(int height, int width)
{
	char	**grid;
	int		i;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(width + 1);
		if (!grid[i])
		{
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (NULL);
		}
		init_grid_row(grid, i, width);
		i++;
	}
	grid[height] = NULL;
	return (grid);
}

static int	init_map_dimensions(char **lines, t_data *data, int *height,
		int *width)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	*height = i;
	if (*height < 3)
	{
		print_error("Map is too small");
		return (0);
	}
	*width = find_map_width(lines);
	data->map = create_map_grid(*height, *width);
	if (!data->map)
	{
		print_error("Memory allocation failed");
		return (0);
	}
	data->map_height = *height;
	data->map_width = *width;
	return (1);
}

int	parse_map_block(char **lines, t_data *data)
{
	int	height;
	int	width;
	int	i;

	if (!init_map_dimensions(lines, data, &height, &width))
		return (0);
	i = 0;
	while (i < height)
	{
		copy_map_line(data->map[i], lines[i], width);
		i++;
	}
	if (!validate_map_chars(data))
		return (0);
	if (!find_player(data))
		return (0);
	return (1);
}
