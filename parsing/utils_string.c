#include "../include/cub3d.h"

/* ========== FUNCTION PROTOTYPES FOR STATIC FUNCTIONS ========== */
static int	has_space(char *s);
static int	word_count(const char *str, char c);
static char	*fill_word(const char *str, int start, int end);
static void	ft_initiate_vars(size_t *i, int *j, int *s_word);

/* ========== STRING UTILITIES ========== */

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	for (size_t i = 0; i <= len; i++)
		res[i] = s[i];
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_free(char **arr, int n)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < n && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* ========== FROM ORIGINAL utils/utils.c ========== */

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

int	check_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char	buffer[1];
	char	*line;
	size_t	len;
	size_t	capacity;
	char	*tmp;

	line = NULL;
	len = 0;
	capacity = 128;
	line = malloc(capacity);
	if (!line)
		return (NULL);
	while (read(fd, buffer, 1) > 0)
	{
		if (len + 1 >= capacity)
		{
			capacity *= 2;
			tmp = realloc(line, capacity);
			if (!tmp)
			{
				free(line);
				return (NULL);
			}
			line = tmp;
		}
		line[len++] = buffer[0];
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

/* ========== FT_SPLIT HELPERS ========== */

static int	word_count(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static void	ft_initiate_vars(size_t *i, int *j, int *s_word)
{
	*i = 0;
	*j = 0;
	*s_word = -1;
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	int		j;
	int		s_word;

	ft_initiate_vars(&i, &j, &s_word);
	res = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			res[j] = fill_word(s, s_word, i);
			if (!(res[j]))
			{
				ft_free(res, j);
				return (NULL);
			}
			s_word = -1;
			j++;
		}
		i++;
	}
	return (res);
}

/* ========== SANITIZE HELPERS ========== */

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

char	**sanitize(char **string)
{
	int		i;
	int		count;
	char	**tmp;

	if (!string)
		return (NULL);
	i = 0;
	count = 0;
	while (string[i])
	{
		if (!has_space(string[i]))
			count++;
		i++;
	}
	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	count = 0;
	while (string[i])
	{
		if (!has_space(string[i]))
		{
			tmp[count] = ft_strdup(string[i]);
			count++;
		}
		i++;
	}
	tmp[count] = NULL;
	return (tmp);
}

/* ========== PARSING SPECIFIC ========== */

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}