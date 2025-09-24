#include "cub3d.h"

void print_error(char *message)
{
    write(2, "Error\n", 6);
    if (message)
        write(2, message, ft_strlen(message));
}

int is_empty_line(char *line)
{
    int i = 0;
    if (!line)
        return 1;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return 0;
        i++;
    }
    return 1;
}

int check_file(char *file, char *ext)
{
    int fd;
    int len;

    len = ft_strlen(file);
    if (len < 4 || ft_strncmp(file + len - 4, ext, 4) != 0)
    {
        print_error("Invalid extension");
        return 0;
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        print_error("File cant be open");
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

int validate_rgb(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return 0;
    return 1;
}

int get_color(char *s)
{
    if (!s)
        return -1; 
    char **rgb = ft_split(s, ',');
    if (!rgb)
        return -1;

    int count = 0;
    while (rgb[count])
        count++;
    
    if (count != 3)
    {
        ft_free(rgb, count);
        return -1;
    }

    int colors[3];
    int i = 0;
    while (i < 3)
    {
        colors[i] = ft_atoi(rgb[i]);
        i++;
    }
    ft_free(rgb, count);

    if (!validate_rgb(colors[0], colors[1], colors[2]))
        return -1;

    return rgb_to_int(colors[0], colors[1], colors[2]);
}

int get_metadata(char *line, t_data *data)
{
    if (!line || is_empty_line(line))
        return 1;

    char **tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0])
    {
        if (tokens) free(tokens);
        return 1;
    }

    if (!tokens[1])
    {
        ft_free(tokens, 1);
        return 1;
    }

    int result = 1;
    
    if (ft_strncmp(tokens[0], "NO", 3) == 0 && !data->north_texture_path && check_file(tokens[1], ".xpm"))
        data->north_texture_path = ft_strdup(tokens[1]);
    else if (ft_strncmp(tokens[0], "SO", 3) == 0 && !data->south_texture_path && check_file(tokens[1], ".xpm"))
        data->south_texture_path = ft_strdup(tokens[1]);
    else if (ft_strncmp(tokens[0], "WE", 3) == 0 && !data->west_texture_path && check_file(tokens[1], ".xpm"))
        data->west_texture_path = ft_strdup(tokens[1]);
    else if (ft_strncmp(tokens[0], "EA", 3) == 0 && !data->east_texture_path && check_file(tokens[1], ".xpm"))
        data->east_texture_path = ft_strdup(tokens[1]);
    else if (ft_strncmp(tokens[0], "F", 2) == 0 && data->floor_color == -1)
        data->floor_color = get_color(tokens[1]);
    else if (ft_strncmp(tokens[0], "C", 2) == 0 && data->ceiling_color == -1)
        data->ceiling_color = get_color(tokens[1]);
    else
    {
        print_error("Duplicate or invalid metadata\n");
        result = 0;
    }
    
    int i = 0;
    while (tokens[i])
        i++;
    ft_free(tokens, i);
    
    return result;
}

void init_data(t_data *data)
{
    data->north_texture_path = NULL;
    data->south_texture_path = NULL;
    data->west_texture_path = NULL;
    data->east_texture_path = NULL;
    data->floor_color = -1;
    data->ceiling_color = -1;
    data->map = NULL;
    data->map_width = 0;
    data->map_height = 0;
    data->player_start_x = -1;
    data->player_start_y = -1;
    data->player_start_direction = '\0';
    data->player_found = 0;
}

int validate_metadata(t_data *data)
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

int fetch_lines(char *file, t_data *data)
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

    while ((line = get_next_line(fd)) != NULL)
    {
        line_number++;
        
        if (is_empty_line(line))
        {
            free(line);
            continue;
        }
        
        if (!get_metadata(line, data))
        {
            free(line);
            close(fd);
            return 0;
        }
        free(line);
        if (data->north_texture_path && data->south_texture_path &&
            data->west_texture_path && data->east_texture_path &&
            data->floor_color != -1 && data->ceiling_color != -1)
        {
            metadata_complete = 1;
            break;
        }
    }
    
    if (!metadata_complete)
    {
        print_error("Incomplete metadata\n");
        close(fd);
        return 0;
    }
    
    // Read map lines
    int map_lines = 0;
    char *map_lines_arr[1024]; // Max 1024 map lines
    
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!is_empty_line(line))
        {
            map_lines_arr[map_lines] = ft_strdup(line);
            map_lines++;
        }
        free(line);
    }
    
    close(fd);
    
    // Store map in data structure
    if (map_lines > 0)
    {
        data->map = malloc(sizeof(char *) * (map_lines + 1));
        if (!data->map)
            return 0;
        
        for (int i = 0; i < map_lines; i++)
        {
            data->map[i] = map_lines_arr[i];
        }
        data->map[map_lines] = NULL;
        data->map_height = map_lines;
        
        // Find map width
        data->map_width = 0;
        for (int i = 0; i < map_lines; i++)
        {
            int len = ft_strlen(data->map[i]);
            if (len > data->map_width)
                data->map_width = len;
        }
    }
    
    return 1;
}