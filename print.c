#include "cub3d.h"

void print_data(t_data *data)
{
    if (!data)
    {
        printf("Data structure is NULL\n");
        return;
    }
    
    printf("=== CUB3D PARSED DATA ===\n\n");
    
    // Print texture paths
    printf("Texture Paths:\n");
    printf("  North: %s\n", data->north_texture_path ? data->north_texture_path : "Not set");
    printf("  South: %s\n", data->south_texture_path ? data->south_texture_path : "Not set");
    printf("  West: %s\n", data->west_texture_path ? data->west_texture_path : "Not set");
    printf("  East: %s\n", data->east_texture_path ? data->east_texture_path : "Not set");
    printf("\n");
    
    // Print colors (convert back from integer to RGB for readability)
    printf("Colors:\n");
    if (data->floor_color != -1)
    {
        int r = (data->floor_color >> 16) & 0xFF;
        int g = (data->floor_color >> 8) & 0xFF;
        int b = data->floor_color & 0xFF;
        printf("  Floor: RGB(%d, %d, %d) [Hex: #%06X]\n", r, g, b, data->floor_color);
    }
    else
    {
        printf("  Floor: Not set\n");
    }
    
    if (data->ceiling_color != -1)
    {
        int r = (data->ceiling_color >> 16) & 0xFF;
        int g = (data->ceiling_color >> 8) & 0xFF;
        int b = data->ceiling_color & 0xFF;
        printf("  Ceiling: RGB(%d, %d, %d) [Hex: #%06X]\n", r, g, b, data->ceiling_color);
    }
    else
    {
        printf("  Ceiling: Not set\n");
    }
    printf("\n");
    
    // Print map information
    printf("Map:\n");
    printf("  Dimensions: %d x %d\n", data->map_width, data->map_height);
    
    if (data->map)
    {
        printf("  Content:\n");
        for (int i = 0; data->map[i]; i++)
        {
            printf("    %s\n", data->map[i]);
        }
    }
    else
    {
        printf("  Map not parsed yet\n");
    }
    printf("\n");
    
    // Print player information
    printf("Player:\n");
    if (data->player_found)
    {
        printf("  Position: (%d, %d)\n", data->player_start_x, data->player_start_y);
        printf("  Direction: %c\n", data->player_start_direction);
    }
    else
    {
        printf("  Player not found in map\n");
    }
    
    printf("=========================\n");
}