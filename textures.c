#include "cub3d.h"

int load_single_texture(t_game *game, t_texture *tex, char *path, char *name)
{
    int height = TEX_HEIGHT;
    int width = TEX_WIDTH;
    
    if (!game || !tex || !path || !name)
        return 0;
    
    tex->img = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
    if (!tex->img)
    {
        print_error("Error\nFailed to load ");
        print_error(name);
        print_error(" texture: ");
        print_error(path);
        print_error("\n");
        return 0;
    }
    
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    if (!tex->addr)
    {
        print_error("Error\nFailed to get data address for ");
        print_error(name);
        print_error(" texture\n");
        mlx_destroy_image(game->mlx.mlx, tex->img);
        tex->img = NULL;
        return 0;
    }
    
    tex->height = height;
    tex->width = width;
    return 1;
}

int load_all_textures(t_game *game)
{
    if (!game)
        return 0;
    
    if (!load_single_texture(game, &game->north_tex, game->data.north_texture_path, "North"))
        return 0;
    if (!load_single_texture(game, &game->south_tex, game->data.south_texture_path, "South"))
    {
        free_textures(game);
        return 0;
    }
    if (!load_single_texture(game, &game->west_tex, game->data.west_texture_path, "West"))
    {
        free_textures(game);
        return 0;
    }
    if (!load_single_texture(game, &game->east_tex, game->data.east_texture_path, "East"))
    {
        free_textures(game);
        return 0;
    }
    return 1;
}

void free_textures(t_game* game)
{
    if (!game || !game->mlx.mlx)
        return;
    
    if (game->north_tex.img)
    {
        mlx_destroy_image(game->mlx.mlx, game->north_tex.img);
        game->north_tex.img = NULL;
    }
    if (game->south_tex.img)
    {
        mlx_destroy_image(game->mlx.mlx, game->south_tex.img);
        game->south_tex.img = NULL;
    }
    if (game->east_tex.img)
    {
        mlx_destroy_image(game->mlx.mlx, game->east_tex.img);
        game->east_tex.img = NULL;
    }
    if (game->west_tex.img)
    {
        mlx_destroy_image(game->mlx.mlx, game->west_tex.img);
        game->west_tex.img = NULL;
    }
}