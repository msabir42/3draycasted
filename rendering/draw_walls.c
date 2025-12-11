#include "../include/cub3d.h"
#include <math.h>

void	draw_walls(t_game *game)
{
	double ray_angle;
	double angle_step;
	double player_angle;
	double start_angle;
	int i;

	i = 0;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	start_angle = player_angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + (i * angle_step);
		draw_slice_to_screen(game, ray_angle, i);
		i++;
	}
}