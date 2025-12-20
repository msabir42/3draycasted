/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:56 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:28:41 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (0);
	if (g < 0 || g > 255)
		return (0);
	if (b < 0 || b > 255)
		return (0);
	return (1);
}

int	rgb_to_int(int r, int g, int b)
{
	return (((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

int	get_color(char *s)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (!s)
		return (-1);
	rgb = ft_split(s, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			ft_free(rgb, 3);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free(rgb, 3);
	if (!validate_rgb(r, g, b))
		return (-1);
	return (rgb_to_int(r, g, b));
}
