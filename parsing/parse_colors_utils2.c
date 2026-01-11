/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_comma_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
		if (s[i++] == ',')
			count++;
	return (count == 2);
}
