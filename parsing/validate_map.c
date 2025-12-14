#include "../include/cub3d.h"

int	validate_metadata(t_data *data)
{
	if (!data->north_texture_path || !data->south_texture_path
		|| !data->west_texture_path || !data->east_texture_path
		|| data->floor_color == -1 || data->ceiling_color == -1)
	{
		print_error("Missing required metadata\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_data *data)
{
	if (!data->player_found)
	{
		print_error("No player starting position found\n");
		return (0);
	}
	if (data->player_start_x == 0 || data->player_start_x == MAP_WIDTH - 1
		|| data->player_start_y == 0 || data->player_start_y == MAP_HEIGHT - 1)
	{
		print_error("Player cannot be on map border\n");
		return (0);
	}
	if (!check_closed_walls(data))
		return (0);
	return (1);
}