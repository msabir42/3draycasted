/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:22:37 by msabir            #+#    #+#             */
/*   Updated: 2025/12/24 20:20:05 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	check_file(char *file, char *ext)
{
	int	fd;
	int	len;

	if (!file || !ext)
		return (0);
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ext, 4) != 0)
		return (print_error("Invalid extension"), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("File can't be opened"), 0);
	close(fd);
	return (1);
}
