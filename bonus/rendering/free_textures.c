/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:10:00 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/19 19:11:09 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_texture_error(t_game *game, t_texture *tex, char *name)
{
	print_error("Error\nFailed to get data address for ");
	print_error(name);
	print_error(" texture\n");
	mlx_destroy_image(game->mlx.mlx, tex->img);
	tex->img = NULL;
	return (0);
}

void	free_textures(t_game *game)
{
	if (!game || !game->mlx.mlx)
		return ;
	if (game->north_tex.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->north_tex.img);
		game->north_tex.img = NULL;
	}
	if (game->south_tex.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->south_tex.img);
		game->south_tex.img = NULL;
	}
	if (game->east_tex.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->east_tex.img);
		game->east_tex.img = NULL;
	}
	if (game->west_tex.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->west_tex.img);
		game->west_tex.img = NULL;
	}
}
