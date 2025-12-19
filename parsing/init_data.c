/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:53 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:26:12 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			data->map[i][j] = 1;
			j++;
		}
		i++;
	}
}

void	init_data(t_data *data)
{
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
	data->west_texture_path = NULL;
	data->east_texture_path = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->map_width = 0;
	data->map_height = 0;
	data->player_start_x = -1;
	data->player_start_y = -1;
	data->player_start_direction = '\0';
	data->player_found = 0;
	init_map(data);
}

void	cleanup_data(t_data *data)
{
	if (data->north_texture_path)
		free(data->north_texture_path);
	if (data->south_texture_path)
		free(data->south_texture_path);
	if (data->west_texture_path)
		free(data->west_texture_path);
	if (data->east_texture_path)
		free(data->east_texture_path);
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
	data->west_texture_path = NULL;
	data->east_texture_path = NULL;
}
