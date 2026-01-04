/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_connectivity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:47:12 by msabir            #+#    #+#             */
/*   Updated: 2025/12/30 00:24:14 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	flood_fill(int **v, t_data *d, int x, int y)
{
	if (x < 0 || x >= d->map_width || y < 0 || y >= d->map_height)
		return ;
	if (v[y][x] || d->map[y][x] == 1)
		return ;
	v[y][x] = 1;
	flood_fill(v, d, x + 1, y);
	flood_fill(v, d, x - 1, y);
	flood_fill(v, d, x, y + 1);
	flood_fill(v, d, x, y - 1);
}

static void	free_visited(int **v, int h)
{
	int	i;

	i = 0;
	while (i < h)
		free(v[i++]);
	free(v);
}

static int	check_cells(int **v, t_data *d, int *unreachable)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while (j < d->map_width)
		{
			if (d->map[i][j] == 0 && !v[i][j])
			{
				print_error("Unreachable areas in map");
				*unreachable = 1;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_connectivity(t_data *data)
{
	int	**visited;
	int	i;
	int	unreachable;

	visited = malloc(sizeof(int *) * data->map_height);
	if (!visited)
		return (print_error("Memory allocation failed"), 0);
	i = 0;
	while (i < data->map_height)
	{
		visited[i] = ft_calloc(data->map_width, sizeof(int));
		if (!visited[i])
		{
			free_visited(visited, i);
			return (print_error("Memory allocation failed"), 0);
		}
		i++;
	}
	flood_fill(visited, data, data->player_start_x, data->player_start_y);
	unreachable = 0;
	check_cells(visited, data, &unreachable);
	free_visited(visited, data->map_height);
	return (!unreachable);
}
