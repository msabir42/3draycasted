/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:05 by msabir            #+#    #+#             */
/*   Updated: 2025/12/30 00:24:14 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	is_map_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	has_map_char = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i])
	{
		if (is_map_valid_char(line[i]))
		{
			if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
				has_map_char = 1;
		}
		else
			return (0);
		i++;
	}
	return (has_map_char);
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
