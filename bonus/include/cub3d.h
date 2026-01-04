/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 06:12:55 by msabir            #+#    #+#             */
/*   Updated: 2026/01/04 20:07:39 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 30
# define MINI_TILE 20
# define OFFSET 20
# define MM_TILE 10
# define MM_VIEW 8
# define MM_POS_X 25
# define MM_POS_Y 25
# define MAP_WIDTH 50
# define MAP_HEIGHT 30
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define SCREEN_W 1500
# define SCREEN_H 900
# define FOV 1.0471975512
# define NUM_RAYS 1500
# define ROT_SPEED 0.025
# define MOV_SPEED 0.05
# define MOUSE_SPEED 0.012

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

typedef struct s_data
{
	char			*north_texture_path;
	char			*south_texture_path;
	char			*west_texture_path;
	char			*east_texture_path;
	int				floor_color;
	int				ceiling_color;
	int				map[MAP_HEIGHT][MAP_WIDTH];
	int				map_width;
	int				map_height;
	int				player_start_x;
	int				player_start_y;
	char			player_start_direction;
	int				player_found;
}					t_data;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mlx;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	double			angle;
}					t_player;

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				esc;
}					t_keys;

typedef struct s_mouse
{
	int				x;
	int				y;
	int				last_x;
	int				enabled;
}					t_mouse;

typedef struct s_game
{
	t_mlx			mlx;
	t_data			data;
	t_player		player;
	t_texture		north_tex;
	t_texture		south_tex;
	t_texture		west_tex;
	t_texture		east_tex;
	t_keys			keys;
	t_mouse			mouse;
	double			wall_height;
}					t_game;

typedef struct s_intersect
{
	double			x_intersect;
	double			y_intersect;
	double			x_step;
	double			y_step;
	double			hit_point_x;
	double			hit_point_y;
	double			dist;
	bool			found;
	int				tile_size;
}					t_intersect;

typedef struct s_ray
{
	double			angle;
	bool			facing_up;
	bool			facing_down;
	bool			facing_left;
	bool			facing_right;
	t_intersect		v_intersect;
	t_intersect		h_intersect;
	bool			found_wall;
	double			dist;
	int				side;
}					t_ray;

typedef struct s_coordinates
{
	double			dx;
	double			dy;
	int				steps;
	double			x_inc;
	double			y_inc;
	double			x;
	double			y;
	double			px;
	double			py;
}					t_coordinates;

typedef struct s_draw_data
{
	int				top;
	int				bottom;
	double			step;
	double			pos;
}					t_draw_data;

typedef struct s_slice_param
{
	int				x;
	t_texture		*tex;
	int				tex_x;
	double			wall_h;
}					t_slice_param;

typedef struct s_parse_state
{
	int				map_started;
	int				row;
}					t_parse_state;

typedef struct s_minimap_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
	int				color;
}					t_minimap_rect;

void			init_data(t_data *data);
int				fetch_lines(char *file, t_data *data);
int				check_file(char *file, char *ext);
int				is_empty_line(char *line);
int				get_metadata(char *line, t_data *data);
int				validate_metadata(t_data *data);
int				get_color(char *s);
int				validate_rgb(int r, int g, int b);
int				is_map_line(char *line);
int				parse_map_line(char *line, t_data *data, int row);
int				validate_map(t_data *data);
int				check_closed_walls(t_data *data);
int				parse_map_block(char **lines, t_data *data);
char			**sanitize(char **string);
int				check_map_connectivity(t_data *data);
void			cleanup_data(t_data *data);

char			**ft_split(const char *s, char c);
void			ft_free(char **strs, int count);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				rgb_to_int(int r, int g, int b);
int				check_newline(char *s);
int				ft_isspace(int c);
char			*get_next_line(int fd);
char			*ft_strchr(const char *s, int c);
int				ft_isdigit(int c);
int				extra_content(char *value_start);
int				validate_metadata_format(char **tokens, char *line);
void			debug_print_map(t_data *data);

void			init_game(t_game *game, t_data data, t_player p);
void			init_player(t_player *p, t_data *data);
void			cast_all_rays(t_game *game);
void			ray_direction(t_ray *ray);
void			find_hit_point(t_ray *ray, t_game *game,
					t_intersect *intersect);
void			ray_vertical_intersection(t_player *p, t_ray *ray,
					t_intersect *inter);
void			ray_horizontal_intersection(t_player *p, t_ray *ray,
					t_intersect *inter);
t_intersect		calculate_distance(t_game *game, t_player *p, t_ray *ray);double			distance(double x1, double x2, double y1, double y2);void			draw_line(t_game *game, t_player *p, t_intersect hit,
					int color);
void			cast_single_ray(t_game *game, double ray_angle);
void			set_values(t_intersect *intersect, double x_next,
					double y_next, t_ray *ray);
void			increment_values(double *x_next, double *y_next,
					t_intersect *intersect);
void			check_horiz_vertic(t_intersect *horiz, t_intersect *vertic,
					t_player *p, t_ray *ray);
void			draw_line_map(t_game *game, t_player *p, t_intersect hit,
					int color);

void			minimap(t_game *game);
void			minimap_fill_rect(t_game *game,
					t_minimap_rect rect);
int				minimap_tile_color(t_game *game,
					int row,
					int col);
void			minimap_draw_single_tile(t_game *game,
					int row_off,
					int col_off);
void			minimap_draw_player_pixel(t_game *game,
					int x,
					int y,
					int radius);

int				close_game(t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			handle_mouse_rotation(t_game *game);
int				mouse_press(int button, int x, int y, t_game *game);
void			mlx_calls(t_game *game);

void			rotate_left(t_player *p);
void			rotate_right(t_player *p);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				game_loop(t_game *game);

void			move_forward(t_game *game);
void			move_right(t_game *game);
void			move_left(t_game *game);
void			move_down(t_game *game);
int				is_movement_valid(t_game *game,
					double new_x,
					double new_y);

void			draw_background(t_game *game,
					int ceiling,
					int floor);
void			clear_screen(t_game *game);
void			my_mlx_pixel_put(t_game *game,
					int x,
					int y,
					int color);
void			draw_slice_to_screen(t_game *game,
					double ray_angle,
					int x);
double			wall_projection_height(t_ray *ray);
void			draw_slice_pixels(t_game *game,
					t_slice_param param);
void			draw_textured_slice(t_game *game,
					int x,
					t_intersect hit,
					t_ray *ray);
void			draw_walls(t_game *game);

int				get_texture_color(t_texture *tex,
					int x,
					int y);
int				handle_texture_error(t_game *game,
					t_texture *tex,
					char *name);
int				load_single_texture(t_game *game,
					t_texture *tex,
					char *path,
					char *name);
int				load_all_textures(t_game *game);
void			free_textures(t_game *game);
int				handle_texture(t_data *data, char **tokens);
void			print_error(char *message);

#endif
