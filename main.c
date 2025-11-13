#include "cub3d.h"

void init_data(t_data *data)
{
    data->ceiling_color =  0xFFFFF8F8;
    data->floor_color = 0xFFFF82B2;
    data->player_start_direction = 'N';
    data->player_start_x = 8;
    data->player_start_y = 5;
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    int i = 0;
    while (i < MAP_HEIGHT)
    {
        int j = 0;
        while (j < MAP_WIDTH)
        {
            data->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}
int main()
{
    t_game *game;
    
    game = malloc(sizeof(t_game));
    init_data(&game->data);
    init_player(&game->player, &game->data);
    init_game(game, game->data, game->player);
    mlx_hook(game->mlx.win, 2, 1L<<0, key_press, game);
    draw_background(game, game->data.ceiling_color, game->data.floor_color);
    // draw_map(game);
    // draw_player(&game->player, game);
    // cast_all_rays(game);
    draw_walls(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
    mlx_loop(game->mlx.mlx);
    return 0;
}

