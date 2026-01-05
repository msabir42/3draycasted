/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:00:56 by msabir            #+#    #+#             */
/*   Updated: 2026/01/01 17:33:41 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_comma_count(char *s);
int	validate_and_split_color(char *s, int *r, int *g, int *b);

int	get_color(char *s)
{
	int	r;
	int	g;
	int	b;

	if (!s)
		return (-1);
	while (ft_strlen(s) > 0 && ft_isspace(s[ft_strlen(s) - 1]))
		s[ft_strlen(s) - 1] = '\0';
	if (!check_comma_count(s))
		return (-1);
	if (!validate_and_split_color(s, &r, &g, &b))
		return (-1);
	return (((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}
