#include "cub3d.h"

int main(int argc, char** argv)
{
    t_data data;
    
    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return 1;
    }
    
    init_data(&data);
    if (!fetch_lines(argv[1], &data))
    {
        printf("Error parsing file\n");
        return 1;
    }
    
    if (!validate_metadata(&data))
    {
        printf("Invalid metadata\n");
        return 1;
    }
    
    print_data(&data);
    
    // Clean up
    if (data.north_texture_path) free(data.north_texture_path);
    if (data.south_texture_path) free(data.south_texture_path);
    if (data.west_texture_path) free(data.west_texture_path);
    if (data.east_texture_path) free(data.east_texture_path);
    if (data.map)
    {
        for (int i = 0; data.map[i]; i++)
            free(data.map[i]);
        free(data.map);
    }
    
    return 0;
}