#include "cub3d.h"

int ft_strcnmp(const char *s1, const char* s2, int n)
{
    int i;

    i  = 0;
    while (s1[i] == s2[i] && i < n)
    {
        i++;
    }
    if (i == n)
        return 1;
    else 
        return 0;
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    char *ret;

    if (!s)
        return (0);
    if (ft_strlen(s) < start)
        len = 0;
    if (ft_strlen(s + start) < len)
        len = ft_strlen(s + start);
    ret = malloc(sizeof(char) * (len + 1));
    if (!ret)
        return (0);
    ft_strlcpy(ret, s + start, len + 1);
    return (ret);
}