/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:15 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:36:44 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	has_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	count_no_space(char **string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (!has_space(string[i]))
			count++;
		i++;
	}
	return (count);
}

static char	**copy_no_space(char **string, int count)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (string[i])
	{
		if (!has_space(string[i]))
		{
			tmp[j] = ft_strdup(string[i]);
			if (!tmp[j])
			{
				ft_free(tmp, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**sanitize(char **string)
{
	int		count;

	if (!string)
		return (NULL);
	count = count_no_space(string);
	return (copy_no_space(string, count));
}
