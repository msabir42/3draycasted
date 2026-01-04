/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/01 17:33:41 by msabir           ###   ########.fr       */
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

static int	count_rgb_elements(char **rgb)
{
	int	count;

	count = 0;
	if (!rgb)
		return (0);
	while (rgb[count])
		count++;
	return (count);
}

static int	is_valid_number(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_rgb_range(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	validate_and_split_color(char *s, int *r, int *g, int *b)
{
	char	**rgb;
	int		count;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (0);
	count = count_rgb_elements(rgb);
	if (count != 3 || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free(rgb, count);
		return (0);
	}
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
	{
		ft_free(rgb, count);
		return (0);
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	ft_free(rgb, count);
	return (validate_rgb_range(*r, *g, *b));
}
