#ifndef CUB3D_H
# define CUB3D_H

// Standard headers
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
    char* north_texture_path;
    char* south_texture_path;
    char* west_texture_path;
    char* east_texture_path;
    int floor_color;
    int ceiling_color;
    char** map;
    int map_width;
    int map_height;
    int player_start_x;
    int player_start_y;
    char player_start_direction;
    int player_found;
} t_data;

// Error handling
void    print_error(char *message);
int     handle_error(char *message, int exit_code);

// Line validation
int     is_empty_line(char *line);

// String utilities
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
int     ft_isspace(int c);
char	**ft_split(char const *s, char c);
void    ft_free(char **strs, int count);
int     ft_atoi(const char *str);
void    *ft_calloc(size_t count, size_t size);
int     ft_strcnmp(const char *s1, const char* s2, int n);

// File parsing
int     check_file(char *file, char *ext);
int     fetch_lines(char *file, t_data *data);
int     get_color(char *s);
int     rgb_to_int(int r, int g, int b);
int     validate_rgb(int r, int g, int b);
void    init_data(t_data *data);
int     validate_metadata(t_data *data);
void    print_data(t_data *data);
int     get_metadata(char *line, t_data *data);
int     spaced_string(char *s);
char    **sanitize(char **string);

// GNL functions
char	*get_next_line(int fd);
int		check_newline(char *s);

// Map validation
int     is_pos(char **map, int map_height);
int     is_valid(char **map, int map_height);
int     is_closed(char **map, int map_height, int x, int y);
void    get_coordinates(t_data *Map, char **map, int map_height);

#endif