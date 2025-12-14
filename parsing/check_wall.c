#include "../include/cub3d.h"

int	check_closed_walls(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (x < MAP_WIDTH)
	{
		if (data->map[0][x] != 1)
		{
			print_error("Top border not completely closed with walls\n");
			return (0);
		}
		if (data->map[MAP_HEIGHT - 1][x] != 1)
		{
			print_error("Bottom border not completely closed with walls\n");
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < MAP_HEIGHT)
	{
		if (data->map[y][0] != 1)
		{
			print_error("Left border not completely closed with walls\n");
			return (0);
		}
		if (data->map[y][MAP_WIDTH - 1] != 1)
		{
			print_error("Right border not completely closed with walls\n");
			return (0);
		}
		y++;
	}
	return (1);
}