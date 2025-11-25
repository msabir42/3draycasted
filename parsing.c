#include "cub3d.h"

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	if (message)
		write(2, message, ft_strlen(message));
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_file(char *file, char *ext)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ext, 4) != 0)
	{
		print_error("Invalid extension\n");
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error("File cant be open\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	spaced_string(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	**sanitize(char **string)
{
	int		i;
	int		count;
	char	**tmp;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (!spaced_string(string[i]))
			count++;
		i++;
	}
	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	count = 0;
	while (string[i])
	{
		if (!spaced_string(string[i]))
		{
			tmp[count] = ft_strdup(string[i]);
			count++;
		}
		i++;
	}
	tmp[count] = NULL;
	return (tmp);
}

int	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	get_color(char *s)
{
	char	**rgb;
	int		color;

	int r, g, b;
	if (!s)
		return (-1);
	rgb = ft_split(s, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free(rgb, 3);
	if (!validate_rgb(r, g, b))
		return (-1);
	color = rgb_to_int(r, g, b);
	return (color);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || is_empty_line(line))
		return 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) &&
			line[i] != '0' && line[i] != '1' &&
			line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'E' && line[i] != 'W' &&
			line[i] != ' ')
			return 0;
		i++;
	}
	return 1;
}

int	parse_map_line(char *line, t_data *data, int row)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (line[i] && col < MAP_WIDTH)
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (data->player_found)
			{
				print_error("Multiple player starting positions\n");
				return 0;
			}
			data->player_start_x = col;
			data->player_start_y = row;
			data->player_start_direction = line[i];
			data->player_found = 1;
			data->map[row][col] = 0; 
		}
		else if (line[i] == ' ')
		{
			data->map[row][col] = 1; 
		}
		else if (line[i] == '0' || line[i] == '1')
		{
			data->map[row][col] = line[i] - '0';
		}
		else if (!ft_isspace(line[i]))
		{
			print_error("Invalid character in map\n");
			return 0;
		}
		if (!ft_isspace(line[i]))
			col++;
		i++;
	}
	
	while (col < MAP_WIDTH)
	{
		data->map[row][col] = 1;
		col++;
	}
	return 1;
}

int	check_closed_walls(t_data *data)
{
	
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		if (data->map[0][x] != 1) 
		{
			print_error("Top border not completely closed with walls\n");
			return 0;
		}
		if (data->map[MAP_HEIGHT - 1][x] != 1) 
		{
			print_error("Bottom border not completely closed with walls\n");
			return 0;
		}
	}
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		if (data->map[y][0] != 1) 
		{
			print_error("Left border not completely closed with walls\n");
			return 0;
		}
		if (data->map[y][MAP_WIDTH - 1] != 1) 
		{
			print_error("Right border not completely closed with walls\n");
			return 0;
		}
	}
	return 1;
}

int	validate_map(t_data *data)
{
	if (!data->player_found)
	{
		print_error("No player starting position found\n");
		return 0;
	}
	if (data->player_start_x == 0 || data->player_start_x == MAP_WIDTH - 1 ||
		data->player_start_y == 0 || data->player_start_y == MAP_HEIGHT - 1)
	{
		print_error("Player cannot be on map border\n");
		return 0;
	}
	if (!check_closed_walls(data))
		return 0;
	return 1;
}

int	get_metadata(char *line, t_data *data)
{
	char	**tokens;
	int		result;
	int		i;

	if (!line || is_empty_line(line))
		return 1;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		if (tokens)
			free(tokens);
		return 1;
	}
	if (!tokens[1])
	{
		ft_free(tokens, 1);
		return 1;
	}
	result = 1;
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
		result = 0;
	}
	else
	{
		print_error("Duplicate or invalid metadata\n");
		result = 0;
	}
	i = 0;
	while (tokens[i])
		i++;
	ft_free(tokens, i);
	return result;
}

void	init_data(t_data *data)
{
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
	data->west_texture_path = NULL;
	data->east_texture_path = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->map_width = 0;
	data->map_height = 0;
	data->player_start_x = -1;
	data->player_start_y = -1;
	data->player_start_direction = '\0';
	data->player_found = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			data->map[i][j] = 1;
		}
	}
}

int	validate_metadata(t_data *data)
{
	if (!data->north_texture_path || !data->south_texture_path ||
		!data->west_texture_path || !data->east_texture_path ||
		data->floor_color == -1 || data->ceiling_color == -1)
	{
		print_error("Missing required metadata\n");
		return 0;
	}
	return 1;
}

int	fetch_lines(char *file, t_data *data)
{
	if (!check_file(file, ".cub"))
		return 0;

	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error("Failed to open file\n");
		return 0;
	}

	char *line;
	int metadata_complete = 0;
	int line_number = 0;
	int map_row = 0;
	int map_started = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		line_number++;

		char *newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';

		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}

		if (!metadata_complete && !map_started)
		{
			if (!get_metadata(line, data))
			{
				free(line);
				close(fd);
				return 0;
			}

			if (data->north_texture_path && data->south_texture_path &&
				data->west_texture_path && data->east_texture_path &&
				data->ceiling_color != -1 && data->floor_color != -1)
			{
				metadata_complete = 1;
			}
		}
		else
		{
			
			
			if (is_map_line(line))
			{
				map_started = 1;
				if (map_row >= MAP_HEIGHT)
				{
					print_error("Map is too tall\n");
					free(line);
					close(fd);
					return 0;
				}

				if (!parse_map_line(line, data, map_row))
				{
					free(line);
					close(fd);
					return 0;
				}
				map_row++;
			}
			else if (!metadata_complete)
			{
				print_error("Invalid line in file\n");
				free(line);
				close(fd);
				return 0;
			}
		}
		free(line);
	}

	close(fd);

	if (!validate_metadata(data))
		return 0;

	if (!validate_map(data))
		return 0;

	return 1;
}