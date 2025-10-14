#include "../cub3d.h"

double wall_projection_height(t_ray *ray)
{
    double projection_height;
    double dist_to_projection_plane;

    dist_to_projection_plane = (SCREEN_W / 2) / tan(FOV / 2);
    if(ray->dist <= 0) ray->dist = 0.001;
    projection_height = (0.5 * dist_to_projection_plane) / ray->dist;
    return projection_height;
}

void draw_slice(t_game *game, int x, double wall_height, int color)
{
    int wall_top;
    int wall_buttom;
    int y;

    wall_top = (SCREEN_H / 2) - (wall_height / 2);
    wall_buttom = (SCREEN_H / 2) + (wall_height / 2);
    if(wall_top < 0) wall_top = 0;
    if(wall_buttom > SCREEN_H) wall_buttom = SCREEN_H;
    y = wall_top;
    while(y < wall_buttom)
    {
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
}

void draw_slice_to_screen(t_game *game, double ray_angle, int x, int color)
{
    t_ray ray;
    t_intersect final_hit;
    double wall_height;
    double player_angle;

    while(ray_angle < 0)
        ray_angle += 2 * M_PI;
    while(ray_angle > 2 * M_PI)
        ray_angle -= 2 * M_PI;
    player_angle = atan2(game->player.dir_y, game->player.dir_x);
    ray.angle = ray_angle;
    ray.found_wall = false;
    ray_direction(&ray);
    final_hit = calculate_distance(game, &game->player, &ray);
    ray.dist *= cos(player_angle - ray_angle);
    if(ray.found_wall)
    {
        wall_height = wall_projection_height(&ray);
        draw_slice(game, x, wall_height, color);
    }
}

void draw_walls(t_game *game)
{
    double ray_angle;
    double angle_step;
    double player_angle;
    double start_angle;
    int i;

    i = 0;
    player_angle = atan2(game->player.dir_y, game->player.dir_x);
    ray_angle = 0;
    start_angle = player_angle - (FOV / 2);
    angle_step = FOV / NUM_RAYS;

    while(i < NUM_RAYS)
    {
        ray_angle = start_angle + (i * angle_step);
        draw_slice_to_screen(game, ray_angle, i, 0xFFFF6B97);
        i++;
    }
}