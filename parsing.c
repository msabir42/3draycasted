#include "cub3d.h"

void print_error(void)
{
    write(2, "Error\n", 6); 
}

int is_line(char *line)
{
    int i = 0;
    if (!line)
        return 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
            && line[i] != '\r' && line[i] != '\v' && line[i] != '\f')
            return 0; 
        i++;
    }
    return 1; 
}

int check_file(char *file)
{
    int fd;
    int len;

    len = ft_strlen(file);
    if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
    {
        print_error();
        return 0;
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        print_error();
        return 0;
    }
    close(fd);
    return 1;
}

int spaced_string(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == ' ')
            return 1;
        i++;
    }
    return 0;
}

char **sanitize(char **string)
{
    int i = 0;
    int count = 0;
    char **tmp;

    while (string[i])
    {
        if (!spaced_string(string[i]))
            count++;
        i++;
    }
    tmp = malloc(sizeof(char *) * (count + 1));
    if (!tmp)
        return NULL;
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
    return tmp;
}

int rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

int get_color(char *s)
{
    if (!s)
        return 0;

    char **rgb = ft_split(s, ',');
    if (!rgb)
        return 0;

    int colors[3];
    int i = 0;
    while (i < 3 && rgb[i])
    {
        colors[i] = ft_atoi(rgb[i]);
        i++;
    }

    i = 0;
    while (rgb[i])
        free(rgb[i++]);
    free(rgb);

    return rgb_to_int(colors[0], colors[1], colors[2]);
}

void get_metadata(char *line, t_data *data)
{
    if (!line)
    {
        print_error();
        return;
    }

    char **meta = sanitize(ft_split(line, ' '));
    if (!meta || !meta[0] || !meta[1])
        return;

    if (ft_strncmp(meta[0], "NO", 3) == 0)
        data->north_texture_path = ft_strdup(meta[1]);
    else if (ft_strncmp(meta[0], "SO", 3) == 0)
        data->south_texture_path = ft_strdup(meta[1]);
    else if (ft_strncmp(meta[0], "WE", 3) == 0)
        data->west_texture_path = ft_strdup(meta[1]);
    else if (ft_strncmp(meta[0], "EA", 3) == 0)
        data->east_texture_path = ft_strdup(meta[1]);
    else if (ft_strncmp(meta[0], "F", 2) == 0)
        data->floor_color = get_color(meta[1]);
    else if (ft_strncmp(meta[0], "C", 2) == 0)
        data->ceiling_color = get_color(meta[1]);

    int i = 0;
    while (meta[i])
        free(meta[i++]);
    free(meta);
}

int fetch_lines(char *file, t_data *data)
{
    if (!check_file(file))
        return 0;

    int fd = open(file, O_RDONLY);
    char *line = get_next_line(fd);

    while (line != NULL)
    {
        get_metadata(line, data);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    return 1;
}
