#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "minilibx-linux/mlx.h" 
# include <stdbool.h>

#define TILE_SIZE 60
#define MAP_WIDTH 16
#define MAP_HEIGHT 10
#define SCREEN_W  (MAP_WIDTH * TILE_SIZE)
#define SCREEN_H  (MAP_HEIGHT * TILE_SIZE)
#define FOV (M_PI / 3)
#define NUM_RAYS SCREEN_W

    

typedef struct s_data
{
    char* north_texture_path;
    char* south_texture_path;
    char* west_texture_path;
    char* east_texture_path;
    int floor_color;
    int ceiling_color;
    int map[MAP_HEIGHT][MAP_WIDTH];
    int map_width;
    int map_height;
    int player_start_x;
    int player_start_y;
    char player_start_direction;
    int player_found;
} t_data;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_mlx;


typedef struct  s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double move_speed;
    double rot_speed;
    double angle;
} t_player;

typedef struct s_game
{
    t_mlx mlx;
    t_data data;
    t_player player;
} t_game;

typedef struct s_intersect
{
    double x_intersect;
    double y_intersect;
    double x_step;
    double y_step;
    double hit_point_x;
    double hit_point_y;
    double dist;
    bool  found;
} t_intersect;

typedef struct s_ray
{
    double angle;
    bool facing_up;
    bool facing_down;
    bool facing_left;
    bool facing_right;
    t_intersect v_intersect;
    t_intersect h_intersect;
    bool found_wall;
    double dist;
} t_ray;

//raycasting
void init_game(t_game *game, t_data data, t_player p);
void draw_background(t_game *game, int ceiling, int floor);
void init_player(t_player *p, t_data *data);
void draw_map(t_game *game);
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
void draw_player(t_player *p, t_game *game);
int key_press(int keycode, t_game *game);
void rotate_left(t_player *p);
void rotate_right(t_player *p);
void cast_all_rays(t_game *game);
void clear_screen(t_game *game);
void draw_walls(t_game *game);
void ray_direction(t_ray *ray);
void find_hit_point(t_ray *ray, t_game *game, t_intersect *intersect);
void ray_vertical_intersection(t_player *p, t_ray *ray, t_intersect *inter);
void ray_horizontal_intersection(t_player *p, t_ray *ray, t_intersect *inter);
t_intersect calculate_distance(t_game *game, t_player *p, t_ray *ray);

#endif