/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:44:02 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:44:57 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	append_char(char **line, char c, size_t *len, size_t *cap)
{
	char	*tmp;

	if (*len + 1 >= *cap)
	{
		*cap *= 2;
		tmp = realloc(*line, *cap);
		if (!tmp)
		{
			free(*line);
			*line = NULL;
			return (0);
		}
		*line = tmp;
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

	cap = 128;
	len = 0;
	line = malloc(cap);
	if (!line)
		return (NULL);
	while (read(fd, buffer, 1) > 0)
	{
		if (!append_char(&line, buffer[0], &len, &cap))
			return (NULL);
		if (buffer[0] == '\n')
			break ;
	}
	if (len == 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}
