#include "cub3d.h"

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (0);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *res;
    size_t i;
    size_t j;

    if (!s1 && !s2)
        return (0);
    res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!res)
        return (0);
    i = 0;
    while (s1 && s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 && s2[j])
        res[i++] = s2[j++];
    res[i] = '\0';
    if (s1)
        free((char *)s1);
    return (res);
}

char *ft_strdup(const char *s)
{
    int i;
    int len;
    char *dup;

    len = 0;
    while (s[len])
        len++;
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}