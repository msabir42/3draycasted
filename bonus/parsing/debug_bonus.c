/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:36:06 by msabir            #+#    #+#             */
/*   Updated: 2025/12/30 01:07:44 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include <stdio.h>

static void	print_row(t_data *d, int y)
{
	int	x;

	printf("Row %2d [%3d cells]: ", y, d->map_width);
	x = 0;
	while (x < d->map_width)
	{
		if (x == d->player_start_x && y == d->player_start_y)
			printf("P");
		else
			printf("%d", d->map[y][x]);
		x++;
	}
	printf(" | last cell = %d\n", d->map[y][d->map_width - 1]);
}

void	debug_print_map(t_data *data)
{
	int	y;

	printf("\n=== MAP DEBUG ===\n");
	printf("Map dimensions: %d x %d\n", data->map_width, data->map_height);
	printf("Player at: (%d, %d) facing '%c'\n",
		data->player_start_x, data->player_start_y,
		data->player_start_direction);
	printf("\nMap content (0=empty, 1=wall):\n");
	y = 0;
	while (y < data->map_height)
	{
		print_row(data, y);
		y++;
	}
	printf("=================\n\n");
}
