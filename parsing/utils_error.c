#include "../include/cub3d.h"

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	if (message)
		write(2, message, ft_strlen(message));
}