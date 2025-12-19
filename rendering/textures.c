/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:35 by oukadir           #+#    #+#             */
/*   Updated: 2025/12/19 19:11:20 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture_data(t_game *game, t_texture *tex, char *name)
{
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (handle_texture_error(game, tex, name));
	return (1);
}

int	load_single_texture(t_game *game, t_texture *tex, char *path, char *name)
{
	int	height;
	int	width;

	height = TEX_HEIGHT;
	width = TEX_WIDTH;
	if (!game || !tex || !path || !name)
		return (0);
	tex->img = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
	if (!tex->img)
	{
		print_error("Error\nFailed to load ");
		print_error(name);
		print_error(" texture: ");
		print_error(path);
		print_error("\n");
		return (0);
	}
	if (!load_texture_data(game, tex, name))
		return (0);
	tex->height = height;
	tex->width = width;
	return (1);
}

static int	load_north_south(t_game *game)
{
	if (!load_single_texture(game, &game->north_tex,
			game->data.north_texture_path, "North"))
	{
		free_textures(game);
		return (0);
	}
	if (!load_single_texture(game, &game->south_tex,
			game->data.south_texture_path, "South"))
	{
		free_textures(game);
		return (0);
	}
	return (1);
}

static int	load_west_east(t_game *game)
{
	if (!load_single_texture(game, &game->west_tex,
			game->data.west_texture_path, "West"))
	{
		free_textures(game);
		return (0);
	}
	if (!load_single_texture(game, &game->east_tex,
			game->data.east_texture_path, "East"))
	{
		free_textures(game);
		return (0);
	}
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!game)
		return (0);
	if (!load_north_south(game))
		return (0);
	if (!load_west_east(game))
		return (0);
	return (1);
}
