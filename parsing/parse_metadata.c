#include "../include/cub3d.h"

int	get_metadata(char *line, t_data *data)
{
	char **tokens;
	int i;

	if (!line || is_empty_line(line))
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		if (tokens)
			free(tokens);
		return (1);
	}
	if (!tokens[1])
	{
		ft_free(tokens, 1);
		return (1);
	}
	i = 0;
	if (ft_strncmp(tokens[0], "NO", 3) == 0 && !data->north_texture_path)
		data->north_texture_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "SO", 3) == 0 && !data->south_texture_path)
		data->south_texture_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "WE", 3) == 0 && !data->west_texture_path)
		data->west_texture_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "EA", 3) == 0 && !data->east_texture_path)
		data->east_texture_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "F", 2) == 0 && data->floor_color == -1)
		data->floor_color = get_color(tokens[1]);
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && data->ceiling_color == -1)
		data->ceiling_color = get_color(tokens[1]);
	else if (is_map_line(line))
	{
		print_error("Map started before metadata was complete\n");
		ft_free(tokens, 2);
		return (0);
	}
	else
	{
		print_error("Duplicate or invalid metadata\n");
		ft_free(tokens, 2);
		return (0);
	}
	while (tokens[i])
		i++;
	ft_free(tokens, i);
	return (1);
}