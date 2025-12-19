/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:48:16 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:49:49 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free(char **arr, int n)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < n)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr)
		memset(ptr, 0, total_size);
	return (ptr);
}
