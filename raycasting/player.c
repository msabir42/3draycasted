#include "../cub3d.h"

void	init_player(t_player *p, t_data *data)
{
	p->pos_x = data->player_start_x + 0.5;
	p->pos_y = data->player_start_y + 0.5;
	if (data->player_start_direction == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (data->player_start_direction == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (data->player_start_direction == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (data->player_start_direction == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
	p->move_speed = 0.08;
	p->rot_speed = 0.03;
	p->angle = M_PI / 4;
}

void	draw_player(t_player *p, t_game *game)
{
	int i;
	int j;
	int pos_x;
	int pos_y;

	i = -3;
	pos_x = p->pos_x * TILE_SIZE;
	pos_y = p->pos_y * TILE_SIZE;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			if (i * i + j * j <= 9)
				my_mlx_pixel_put(game, pos_x + i, pos_y + j, 0xFFFF00);
			j++;
		}
		i++;
	}
}