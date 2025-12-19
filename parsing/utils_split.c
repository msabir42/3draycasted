/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:08:18 by msabir            #+#    #+#             */
/*   Updated: 2025/12/19 03:37:27 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	word_count(const char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*copy_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	assign_words(char **res, const char *s, char c)
{
	size_t	i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			res[j] = copy_word(s, start, i);
			if (!res[j])
				return (ft_free(res, j), 0);
			start = -1;
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!assign_words(res, s, c))
		return (NULL);
	return (res);
}
