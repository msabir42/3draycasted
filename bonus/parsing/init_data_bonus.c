/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:53 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:28:38 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_data(t_data *data)
{
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
	data->west_texture_path = NULL;
	data->east_texture_path = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_start_x = -1;
	data->player_start_y = -1;
	data->player_start_direction = '\0';
	data->player_found = 0;
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->north_texture_path)
		free(data->north_texture_path);
	if (data->south_texture_path)
		free(data->south_texture_path);
	if (data->west_texture_path)
		free(data->west_texture_path);
	if (data->east_texture_path)
		free(data->east_texture_path);
	if (data->map)
	{
		i = 0;
		while (i < data->map_height && data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
	data->west_texture_path = NULL;
	data->east_texture_path = NULL;
	data->map = NULL;
}
