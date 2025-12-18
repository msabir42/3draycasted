#include "../include/cub3d.h"

int	parse_map_line(char *line, t_data *data, int row)
{
	int i;
	int col;

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
				return (0);
			}
			data->player_start_x = col;
			data->player_start_y = row;
			data->player_start_direction = line[i];
			data->player_found = 1;
			data->map[row][col] = 0;  
		}
		else if (line[i] == ' ')      
			data->map[row][col] = 0;
		else if (line[i] == '0')
			data->map[row][col] = 0;  
		else if (line[i] == '1')
			data->map[row][col] = 1; 
		else if (line[i] != '\t' && line[i] != '\n' && line[i] != '\r' && 
				 line[i] != '\v' && line[i] != '\f')  
		{
			print_error("Invalid character in map\n");
			return (0);
		}
				if (line[i] == ' ' || line[i] == '0' || line[i] == '1' || 
			line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			col++;
		}
		i++;
	}
	if(col > data->map_width)
		data->map_width = col;
	while (col < MAP_WIDTH)
	{
		data->map[row][col] = 1;
		col++;
	}
	return (1);
}
