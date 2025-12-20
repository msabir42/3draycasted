/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:36:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 17:46:33 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"
#include <stdlib.h>

static void	exit_error(t_game *game, char *msg)
{
	if (msg)
		print_error(msg);
	if (game)
	{
		free_textures(game);
		cleanup_data(&game->data);
		free(game);
	}
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3D map.cub\n");
		return (1);
	}

	game = malloc(sizeof(t_game));
	if (!game)
	{
		print_error("Malloc failed\n");
		return (1);
	}

	ft_bzero(game, sizeof(t_game));

	init_data(&game->data);

	if (!fetch_lines(argv[1], &game->data))
		exit_error(game, "Failed to parse map\n");

	init_player(&game->player, &game->data);

	init_game(game, game->data, game->player);

	if (!load_all_textures(game))
		exit_error(game, "Failed to load textures\n");

	mlx_calls(game);

	free_textures(game);
	cleanup_data(&game->data);
	free(game);
	return (0);
}
