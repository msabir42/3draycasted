/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:36:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:25:46 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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

int	main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		exit_error(NULL, "Usage: ./cub3D map.cub");

	game = malloc(sizeof(t_game));
	if (!game)
		exit_error(NULL, "Malloc failed");

	ft_bzero(game, sizeof(t_game));
	init_data(&game->data);

	if (!fetch_lines(argv[1], &game->data))
		exit_error(game, "Failed to parse map\n");

	init_player(&game->player, &game->data);
	init_game(game, game->data, game->player);

	if (!load_all_textures(game))
		exit_error(game, "Failed to load textures\n");

	mlx_calls(game);

	cleanup_mlx(game);
	free_textures(game);
	cleanup_data(&game->data);
	free(game);
	return (0);
}