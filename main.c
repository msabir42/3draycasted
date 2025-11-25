#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_game *game;
	char *map_file;

	if (argc != 2)
	{
		print_error("Usage: ./cube map.cub\n");
		return (1);
	}

	map_file = argv[1];
	game = malloc(sizeof(t_game));
	if (!game)
	{
		print_error("Malloc failed\n");
		return (1);
	}

	init_data(&game->data);

	if (!fetch_lines(map_file, &game->data))
	{
		print_error("Failed to parse map\n");
		free(game);
		return (1);
	}

	init_player(&game->player, &game->data);
	printf("Floor color: 0x%X\n", game->data.floor_color);
	printf("Ceiling color: 0x%X\n", game->data.ceiling_color);

	init_game(game, game->data, game->player);

	printf("Loading textures...\n");
	if (!load_all_textures(game))
	{
		print_error("Failed to load textures\n");
		free(game);
		return (1);
	}
	printf("Textures loaded successfully!\n");

	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	draw_background(game, game->data.ceiling_color, game->data.floor_color);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	mlx_loop(game->mlx.mlx);

	free(game);
	return (0);
}