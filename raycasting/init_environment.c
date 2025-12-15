#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;

	pixel = game->mlx.addr + (y * game->mlx.line_len + x * (game->mlx.bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_background(t_game *game, int ceiling_color, int floor_color)
{
	int x;
	int y;

	y = 0;
	while (y < SCREEN_H / 2)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}