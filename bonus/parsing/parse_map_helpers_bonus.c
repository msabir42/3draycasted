/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/01 17:33:41 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	pad_row_with_walls(t_data *data, int row, int col)
{
	while (col < MAP_WIDTH)
	{
		data->map[row][col] = 1;
		col++;
	}
	return (1);
}
