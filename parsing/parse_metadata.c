/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:31:35 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:28:49 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	set_color(t_data *data, char *id, char *value)
{
	int	color;

	color = get_color(value);
	if (color == -1)
		return (0);
	if (ft_strncmp(id, "F", 2) == 0 && data->floor_color == -1)
		data->floor_color = color;
	else if (ft_strncmp(id, "C", 2) == 0 && data->ceiling_color == -1)
		data->ceiling_color = color;
	else
		return (print_error("Duplicate or invalid color"), 0);
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

static int	process_tokens(t_data *data, char **tokens, char *line)
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
		return (print_error("Map started before metadata was complete"), 0);
	return (1);
}

int	get_metadata(char *line, t_data *data)
{
	char	**tokens;
	int		res;

	if (!line || is_empty_line(line))
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		if (tokens)
			ft_free(tokens, 2);
		return (1);
	}
	res = process_tokens(data, tokens, line);
	ft_free(tokens, 2);
	return (res);
}
