#include "cub3d.h"

static char *ft_swap(char *s, char *buffer)
{
    char *swapped;

    if (!s)
        swapped = ft_strdup(buffer);
    else
        swapped = ft_strjoin(s, buffer);
    return (swapped);
}

static char *check_if_line(char *s)
{
    int i;
    char *str;
    int j;

    if (!s)
        return (NULL);
    i = 0;
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    str = malloc(i + 1);
    if (!str)
        return (NULL);
    j = 0;
    while (j < i)
    {
        str[j] = s[j];
        j++;
    }
    str[j] = '\0';
    return (str);
}

static char *get_remain(char *s)
{
    int i;
    int len;
    char *remain;

    i = 0;
    if (!s || *s == '\0')
        return (NULL);
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    len = ft_strlen(s);
    if (i >= len)
    {
        free(s);
        return (NULL);
    }
    remain = ft_strdup(s + i);
    free(s);
    return (remain);
}

static char *read_fd(int fd, char *string)
{
    int is_read;
    char *buffer;

    buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    while (1)
    {
        is_read = read(fd, buffer, BUFFER_SIZE);
        if (is_read <= 0)
        {
            free(buffer);
            return (string);
        }
        buffer[is_read] = '\0';
        string = ft_swap(string, buffer);
        if (check_newline(string))
            break ;
    }
    free(buffer);
    return (string);
}

char *get_next_line(int fd)
{
    static char *string;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    string = read_fd(fd, string);
    if (!string)
        return (NULL);
    line = check_if_line(string);
    string = get_remain(string);
    return (line);
}