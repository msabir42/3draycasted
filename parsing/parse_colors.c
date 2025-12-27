/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:56 by msabir            #+#    #+#             */
/*   Updated: 2025/12/26 18:35:13 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_number(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

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

static int	validate_and_parse_rgb(char **rgb, int *r, int *g, int *b)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
		return (0);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (!validate_rgb(*r, *g, *b))
		return (0);
	return (1);
}

int	get_color(char *s)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	if (!s)
		return (-1);
	while (ft_strlen(s) > 0 && ft_isspace(s[ft_strlen(s) - 1]))
		s[ft_strlen(s) - 1] = '\0';
	rgb = ft_split(s, ',');
	if (!rgb)
		return (-1);
	if (!validate_and_parse_rgb(rgb, &r, &g, &b))
	{
		ft_free(rgb, 3);
		return (-1);
	}
	color = rgb_to_int(r, g, b);
	ft_free(rgb, 3);
	return (color);
}
