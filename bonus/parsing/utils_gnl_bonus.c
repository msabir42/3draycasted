/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:44:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/21 02:25:04 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	gnl_grow(char **line, size_t *cap, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(*cap * 2);
	if (!tmp)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = (*line)[i];
		i++;
	}
	free(*line);
	*line = tmp;
	*cap *= 2;
	return (1);
}

static int	gnl_push(char **line, char c, size_t *len, size_t *cap)
{
	if (*len + 1 >= *cap)
	{
		if (!gnl_grow(line, cap, *len))
			return (0);
	}
	(*line)[*len] = c;
	(*len)++;
	return (1);
}

static int	gnl_read(int fd, char **line, size_t *len, size_t *cap)
{
	char	buffer[1];
	ssize_t	r;

	r = read(fd, buffer, 1);
	while (r > 0)
	{
		if (!gnl_push(line, buffer[0], len, cap))
			return (-1);
		if (buffer[0] == '\n')
			break ;
		r = read(fd, buffer, 1);
	}
	return (r);
}

char	*get_next_line(int fd)
{
	char	*line;
	size_t	len;
	size_t	cap;
	int		r;

	cap = 128;
	len = 0;
	line = malloc(cap);
	if (!line)
		return (NULL);
	r = gnl_read(fd, &line, &len, &cap);
	if (r < 0 || len == 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}
