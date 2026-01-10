/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 17:19:32 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_map_width(char **lines)
{
	int	i;
	int	j;
	int	max_width;

	max_width = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '\n')
				break ;
			j++;
		}
		if (j > max_width)
			max_width = j;
		i++;
	}
	return (max_width);
}

void	init_grid_row(char **grid, int i, int width)
{
	int	j;

	j = 0;
	while (j < width)
		grid[i][j++] = ' ';
	grid[i][width] = '\0';
}

void	copy_map_line(char *grid_line, char *file_line, int width)
{
	int	i;

	i = 0;
	while (file_line[i] && file_line[i] != '\n' && i < width)
	{
		grid_line[i] = file_line[i];
		i++;
	}
	while (i < width)
		grid_line[i++] = ' ';
	grid_line[width] = '\0';
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
