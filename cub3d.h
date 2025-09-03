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

// Configuration constants
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SUCCESS 0
# define ERROR 1
# define MAP_CHARS "01NSEW "
# define PLAYER_CHARS "NSEW"

// Error messages
# define ERR_FILE_OPEN "Could not open file"
# define ERR_FILE_EXT "Invalid file extension"
# define ERR_MAP "Invalid map"
# define ERR_TEXTURE "Invalid texture"
# define ERR_COLOR "Invalid color"
# define ERR_MEMORY "Memory allocation failed"
# define ERR_PLAYER "Invalid player configuration"

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

// File parsing
int     check_file(char *file);
int     fetch_lines(char *file, t_data *data);
int     get_color(char *s);
int     rgb_to_int(int r, int g, int b);
int     validate_rgb(int r, int g, int b);
void    init_data(t_data *data);
int     validate_metadata(t_data *data);
void    print_data(t_data *data);


// GNL functions
char	*get_next_line(int fd);
int		check_newline(char *s);

#endif