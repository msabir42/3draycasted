#include "..//include/cub3d.h"


void init_data(t_data *data)
{
int i;
int j;


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
i = 0;
while (i < MAP_HEIGHT)
{
j = 0;
while (j < MAP_WIDTH)
{
data->map[i][j] = 1;
j++;
}
i++;
}
}