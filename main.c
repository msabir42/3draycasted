#include "cub3d.h"


int main(int argc, char** argv)
{
    t_data* data;
    if (argc == 2)
    {
        char *file_name = argv[1];
        init_data(data);
        fetch_lines(file_name,data);
        
    }
}