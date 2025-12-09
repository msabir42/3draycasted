#include "../include/cub3d.h"



int is_map_line(char *line);
int parse_map_line(char *line, t_data *data, int row);


int parse_map_block(char **lines, t_data *data)
{
int i;


i = 0;
while (lines[i])
{
if (i >= MAP_HEIGHT)
{
print_error("Map is too tall\n");
return (0);
}
if (!parse_map_line(lines[i], data, i))
return (0);
i++;
}
return (1);
}