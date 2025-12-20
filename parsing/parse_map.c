/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:28:45 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_map_block(char **lines, t_data *data)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (i >= MAP_HEIGHT)
		{
			print_error("Map is too tall");
			return (0);
		}
		if (!parse_map_line(lines[i], data, i))
			return (0);
		i++;
	}
	return (1);
}
