#include "../include/cub3d.h"


void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
	if (game->data.map[(int)new_y][(int)new_x] == 0)
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
	if (game->data.map[(int)new_y][(int)new_x] == 0)
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
	if (game->data.map[(int)new_y][(int)new_x] == 0)
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	move_down(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.dir_y * game->player.move_speed;
	if (game->data.map[(int)new_y][(int)new_x] == 0)
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}
int	key_press(int keycode, t_game *game)
{
	if (keycode == 13 || keycode == 119)
		move_forward(game);
	else if (keycode == 1 || keycode == 115)
		move_down(game);
	else if (keycode == 0 || keycode == 97)
		move_left(game);
	else if (keycode == 2 || keycode == 100)
		move_right(game);
	else if (keycode == 113 || keycode == 65361)
		rotate_left(&game->player);
	else if (keycode == 101 || keycode == 65363)
		rotate_right(&game->player);
	else if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		exit(0);
		//free all memo later
	}
	clear_screen(game);
	draw_background(game, game->data.ceiling_color, game->data.floor_color);
	draw_walls(game);
	// draw_map(game);
	// draw_player(&game->player, game);
	// cast_all_rays(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}