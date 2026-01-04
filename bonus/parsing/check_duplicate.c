/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 18:18:45 by msabir            #+#    #+#             */
/*   Updated: 2025/12/29 17:48:57 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

int	validate_metadata_format(char **tokens, char *line)
{
	int	token_count;

	(void)line;
	token_count = count_tokens(tokens);
	if (token_count != 2)
	{
		print_error("Invalid metadata format - should have exactly 2 elements");
		return (0);
	}
	return (1);
}
