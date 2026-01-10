/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_lines_helper_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 22:53:23 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	expand_capacity(char ***lines, int *capacity, int count)
{
	char	**tmp;
	int		i;

	*capacity *= 2;
	tmp = malloc(sizeof(char *) * (*capacity));
	if (!tmp)
		return (0);
	i = -1;
	while (++i < count)
		tmp[i] = (*lines)[i];
	free(*lines);
	*lines = tmp;
	return (1);
}

int	read_and_store_lines(int fd, char ***lines, int *count)
{
	char	*line;
	char	*newline_pos;
	int		capacity;

	capacity = 100;
	*lines = malloc(sizeof(char *) * capacity);
	if (!*lines)
		return (0);
	*count = 0;
	line = get_next_line(fd);
	while (line)
	{
		newline_pos = ft_strchr(line, '\n');
		if (newline_pos)
			*newline_pos = '\0';
		if (*count >= capacity - 1)
			if (!expand_capacity(lines, &capacity, *count))
				return (0);
		(*lines)[(*count)++] = line;
		line = get_next_line(fd);
	}
	(*lines)[*count] = NULL;
	return (1);
}

void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(lines[i++]);
	free(lines);
}
