/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:05 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 23:45:35 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || is_empty_line(line))
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	set_texture(t_data *data, char *id, char *path)
{
	char	*new_path;

	new_path = ft_strdup(path);
	if (!new_path)
		return (0);
	if (ft_strncmp(id, "NO", 3) == 0 && !data->north_texture_path)
		data->north_texture_path = new_path;
	else if (ft_strncmp(id, "SO", 3) == 0 && !data->south_texture_path)
		data->south_texture_path = new_path;
	else if (ft_strncmp(id, "WE", 3) == 0 && !data->west_texture_path)
		data->west_texture_path = new_path;
	else if (ft_strncmp(id, "EA", 3) == 0 && !data->east_texture_path)
		data->east_texture_path = new_path;
	else
	{
		free(new_path);
		return (print_error("Duplicate or invalid texture"), 0);
	}
	return (1);
}

int	handle_texture(t_data *data, char **tokens)
{
	if (ft_strncmp(tokens[0], "NO", 3) == 0)
		return (set_texture(data, "NO", tokens[1]));
	if (ft_strncmp(tokens[0], "SO", 3) == 0)
		return (set_texture(data, "SO", tokens[1]));
	if (ft_strncmp(tokens[0], "WE", 3) == 0)
		return (set_texture(data, "WE", tokens[1]));
	if (ft_strncmp(tokens[0], "EA", 3) == 0)
		return (set_texture(data, "EA", tokens[1]));
	return (-1);
}
