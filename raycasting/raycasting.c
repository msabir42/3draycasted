#include "../cub3d.h"

double distance(double x1, double x2, double y1, double y2)
{
    double dst;

    dst = sqrt((x2- x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return dst;
}

t_intersect calculate_distance(t_game *game, t_player *p, t_ray *ray)
{
    t_intersect horiz;
    t_intersect vertic;

    ray_horizontal_intersection(p, ray, &horiz);
    ray_vertical_intersection(p, ray, &vertic);
    find_hit_point(ray, game, &horiz);
    find_hit_point(ray, game, &vertic);
    horiz.dist = 100000;
    vertic.dist = 100000;
    if(horiz.found)
        horiz.dist = distance(p->pos_x, horiz.hit_point_x, p->pos_y, horiz.hit_point_y);
    if(vertic.found)
        vertic.dist = distance(p->pos_x, vertic.hit_point_x, p->pos_y, vertic.hit_point_y);
    if(horiz.found || vertic.found)
        ray->found_wall = true;
    if(horiz.dist < vertic.dist)
    {
        ray->dist = horiz.dist;
        return (horiz);
    }
    else
    {
        ray->dist = vertic.dist;
        return (vertic);
    }
}

void draw_line(t_game *game, double x0, double y0, double x1, double y1, int color)
{
    double dx;
    double dy;
    int steps;
    double x_inc;
    double y_inc;
    double x;
    double y;
    double px;
    double py;
    int i;

    i = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    steps = (int)fmax(fabs(dx), fabs(dy));
    if(steps == 0)
        return;
    x_inc = dx / steps;
    y_inc = dy / steps;
    x = x0;
    y = y0;
    while(i <= steps)
    {
        px = (int)x;
        py = (int)y;
        if(px >= 0 || px < SCREEN_W || py >= 0 || py < SCREEN_H)
            my_mlx_pixel_put(game, px, py, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void cast_single_ray(t_game *game, double ray_angle)
{
    t_ray ray;
    t_intersect final_hit;

    while(ray_angle < 0)
        ray_angle += 2 * M_PI;
    while(ray_angle > 2 * M_PI)
        ray_angle -= 2 * M_PI;
    
    ray.angle = ray_angle;
    ray.found_wall = false;
    ray_direction(&ray);
    final_hit = calculate_distance(game, &game->player, &ray);
    if(ray.found_wall)
    {
        draw_line(game, game->player.pos_x * TILE_SIZE, 
                game->player.pos_y * TILE_SIZE, 
                final_hit.hit_point_x * TILE_SIZE, 
                final_hit.hit_point_y * TILE_SIZE,
                0xFF0000);
        }
}

void cast_all_rays(t_game *game)
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
        cast_single_ray(game, ray_angle);
        i++;
    }
}