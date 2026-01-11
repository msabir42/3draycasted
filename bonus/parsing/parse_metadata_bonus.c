/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:31:35 by msabir            #+#    #+#             */
/*   Updated: 2025/12/31 10:24:06 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	set_color(t_data *data, char *id, char *value)
{
	int	color;

	color = get_color(value);
	if (color == -1)
		return (0);
	if (ft_strncmp(id, "F", 2) == 0)
	{
		if (data->floor_color != -1)
			return (print_error("Duplicate floor color"), 0);
		data->floor_color = color;
	}
	else if (ft_strncmp(id, "C", 2) == 0)
	{
		if (data->ceiling_color != -1)
			return (print_error("Duplicate ceiling color"), 0);
		data->ceiling_color = color;
	}
	else
		return (print_error("Invalid color identifier"), 0);
	return (1);
}

static int	handle_color(t_data *data, char **tokens)
{
	if (ft_strncmp(tokens[0], "F", 2) == 0)
		return (set_color(data, "F", tokens[1]));
	if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (set_color(data, "C", tokens[1]));
	return (-1);
}

static int	process_metadata_type(t_data *data, char **tokens, char *line)
{
	int	res;

	res = handle_texture(data, tokens);
	if (res == 0)
		return (0);
	if (res == -1)
	{
		res = handle_color(data, tokens);
		if (res == 0)
			return (0);
	}
	if (res == -1 && is_map_line(line))
		return (print_error(
				"Map started before metadata was complete"), 0);
	return (1);
}

static int	parse_color_line(t_data *data, char *line)
{
	int		i;
	char	*color_part;
	char	color_id;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	if (line[i] != 'F' && line[i] != 'C')
		return (-1);
	color_id = line[i];
	i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	color_part = line + i;
	if (color_id == 'F')
		return (set_color(data, "F", color_part));
	return (set_color(data, "C", color_part));
}

int	get_metadata(char *line, t_data *data)
{
	char	**tokens;
	int		res;
	int		color_res;

	if (!line || is_empty_line(line))
		return (1);
	color_res = parse_color_line(data, line);
	if (color_res != -1)
		return (color_res);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		if (tokens)
			ft_free_all(tokens);
		return (1);
	}
	if (!validate_metadata_format(tokens, line))
	{
		ft_free_all(tokens);
		return (0);
	}
	res = process_metadata_type(data, tokens, line);
	ft_free_all(tokens);
	return (res);
}
