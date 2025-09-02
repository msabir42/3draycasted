#ifndef CUB3D_H
#define CUB3D_H


# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
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
}					t_data;

void    print_error();
int     is_line(char *line);
int     ft_isspace(int c);
char**  ft_split(const char *s, char c);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strcnmp(const char *s1, const char* s2, int n);
int		check_newline(char *s);



#endif