#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;

	pixel = game->mlx.addr + (y * game->mlx.line_len + x * (game->mlx.bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (game->data.map[i][j] == 1)
				color = 0xFFFFFF;
			else
				color = 0x454545;
			draw_tile(game, j * TILE_SIZE, i * TILE_SIZE, color);
			j++;
		}
		i++;
	}
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