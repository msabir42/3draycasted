/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:44:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/20 21:31:05 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	append_char(char **line, char c, size_t *len, size_t *cap)
{
	char	*tmp;
	size_t	i;
	size_t	new_cap;

	if (*len + 1 >= *cap)
	{
		new_cap = *cap * 2;
		tmp = malloc(new_cap);
		if (!tmp)
		{
			free(*line);
			*line = NULL;
			return (0);
		}
		i = 0;
		while (i < *len)
		{
			tmp[i] = (*line)[i];
			i++;
		}
		free(*line);
		*line = tmp;
		*cap = new_cap;
	}
	(*line)[(*len)++] = c;
	return (1);
}

char	*get_next_line(int fd)
{
	char	buffer[1];
	char	*line;
	size_t	len;
	size_t	cap;
	ssize_t	bytes_read;

	cap = 128;
	len = 0;
	line = malloc(cap);
	if (!line)
		return (NULL);
	bytes_read = read(fd, buffer, 1);
	while (bytes_read > 0)
	{
		if (!append_char(&line, buffer[0], &len, &cap))
		{
			return (NULL);
		}
		if (buffer[0] == '\n')
			break ;
		bytes_read = read(fd, buffer, 1);
	}
	if (bytes_read < 0 || len == 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}
