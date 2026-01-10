/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:01:11 by msabir            #+#    #+#             */
/*   Updated: 2026/01/10 22:53:23 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error(char *message)
{
	static int	error_printed = 0;

	if (!error_printed)
	{
		write(2, "Error\n", 6);
		error_printed = 1;
	}
	if (message)
	{
		write(2, message, ft_strlen(message));
		if (message[ft_strlen(message) - 1] != '\n')
			write(2, "\n", 1);
	}
}

void	ft_bzero(void *s, size_t n)
{
	char	*tmp_ptr;

	tmp_ptr = (char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = 0;
		n--;
	}
}
