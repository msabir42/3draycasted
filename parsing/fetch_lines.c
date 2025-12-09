#include "../include/cub3d.h"


char *get_next_line(int fd);


int check_file(char *file, char *ext)
{
int fd;
int len;


if (!file || !ext)
return (0);
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

int fetch_lines(char *file, t_data *data)
{
int fd;
char *line;
int metadata_complete;
int map_row;
int map_started;


if (!check_file(file, ".cub"))
return (0);
fd = open(file, O_RDONLY);
if (fd == -1)
{
print_error("Failed to open file\n");
return (0);
}
metadata_complete = 0;
map_row = 0;
map_started = 0;
while ((line = get_next_line(fd)) != NULL)
{
char *tmp;


tmp = ft_strchr(line, '\n');
if (tmp)
*tmp = '\0';
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
return (0);
}
if (data->north_texture_path && data->south_texture_path
&& data->west_texture_path && data->east_texture_path
&& data->ceiling_color != -1 && data->floor_color != -1)
metadata_complete = 1;
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
return (0);
}
if (!parse_map_line(line, data, map_row))
{
free(line);
close(fd);
return (0);
}
map_row++;
}
else if (!metadata_complete)
{
print_error("Invalid line in file\n");
free(line);
close(fd);
return (0);
}
}
free(line);
}
close(fd);
if (!validate_metadata(data))
return (0);
if (!validate_map(data))
return (0);
return (1);
}