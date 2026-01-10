/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:20 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:26 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_metadata(t_data *data)
{
	if (!data->north_texture_path || !data->south_texture_path
		|| !data->west_texture_path || !data->east_texture_path
		|| data->floor_color == -1 || data->ceiling_color == -1)
	{
		print_error("Missing required metadata");
		return (0);
	}
	return (1);
}

int	validate_map(t_data *data)
{
	if (!data->player_found)
	{
		print_error("No player starting position found");
		return (0);
	}
	if (!check_map_walls(data))
		return (0);
	return (1);
}
