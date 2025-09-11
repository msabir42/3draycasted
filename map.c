#include "cub3d.h"

int is_pos(char **map, int map_height)
{
    int i = 0;
    int flag = 0;
    char north = 'N';
    char south = 'S';
    char west  = 'W';
    char east  = 'E';

    while (i < map_height)
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == north || map[i][j] == south
                || map[i][j] == west || map[i][j] == east)
            {
                if (flag == 0)
                    flag = 1; 
                else
                    return 0; 
            }
            j++;
        }
        i++;
    }
    return flag;
}

int is_valid(char **map, int map_height)
{
    int i = 0;
    char wall = '1';
    char empty_space = '0';
    char space = ' ';
    char north = 'N';
    char south = 'S';
    char west  = 'W';
    char east  = 'E';

    while (i < map_height)
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == north || map[i][j] == south
                || map[i][j] == west || map[i][j] == east || map[i][j] == space || map[i][j] == empty_space || map[i][j] == wall )
            {
                j++;
            }
            else 
                return 0;
        }
        i++;
    }
    return 1;
}

int is_closed(char **map, int map_height, int x, int y)
{
    int row_len;

    if (x < 0 || x >= map_height)
        return 0;

    row_len = 0;
    while (map[x][row_len])
        row_len++;

    if (y < 0 || y >= row_len)
        return 0;

    if (map[x][y] == '1' || map[x][y] == 'v')
        return 1;

    if (map[x][y] == ' ')
        return 1;

    map[x][y] = 'v';

    if (!is_closed(map, map_height, x+1, y)) return 0;
    if (!is_closed(map, map_height, x-1, y)) return 0;
    if (!is_closed(map, map_height, x, y+1)) return 0;
    if (!is_closed(map, map_height, x, y-1)) return 0;

    return 1;
}

void get_coordinates(t_data *Map, char **map, int map_height)
{
    int i = 0;
    int flag = 0;

    while (i < map_height)
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S'
                || map[i][j] == 'W' || map[i][j] == 'E')
            {
                if (flag)
                {
                    printf("Error: multiple players found\n");
                    exit(1);
                }
                Map->player_start_x = i;
                Map->player_start_y = j;
                Map->player_start_direction = map[i][j];
                flag = 1;
                map[i][j] = '0';
            }
            j++;
        }
        i++;
    }

    if (!flag)
    {
        printf("Error: no player found\n");
        exit(1);
    }
}