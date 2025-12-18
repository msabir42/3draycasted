#include "../include/cub3d.h"

int	is_map_line(char *line)
{
	int i;

	i = 0;
	if (!line || is_empty_line(line))
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}