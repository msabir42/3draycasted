/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:36:02 by msabir            #+#    #+#             */
/*   Updated: 2026/01/04 08:22:40 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static void	cleanup_mlx(t_game *game)
{
	if (!game || !game->mlx.mlx)
		return ;
	if (game->mlx.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
		game->mlx.img = NULL;
	}
	if (game->mlx.win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		game->mlx.win = NULL;
	}
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	game->mlx.mlx = NULL;
}

static void	exit_error(t_game *game, char *msg)
{
	if (msg)
		print_error(msg);
	if (game)
	{
		cleanup_mlx(game);
		free_textures(game);
		cleanup_data(&game->data);
		free(game);
	}
	exit(1);
}

static void	run_game(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_error(NULL, "Malloc failed\n");
	ft_bzero(game, sizeof(t_game));
	init_data(&game->data);
	if (!fetch_lines(map_path, &game->data))
		exit_error(game, "Failed to parse map\n");
	init_player(&game->player, &game->data);
	init_game(game, game->data, game->player);
	if (!load_all_textures(game))
	{
		print_error("Failed to load textures\n");
		close_game(game);
	}
	mlx_calls(game);
	cleanup_mlx(game);
	free_textures(game);
	cleanup_data(&game->data);
	free(game);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit_error(NULL, "Usage: ./cub3D map.cub\n");
	run_game(argv[1]);
	return (0);
}
