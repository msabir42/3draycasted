#include "../include/cub3d.h"
size_t ft_strlen(char *s)
{
size_t i;


if (!s)
return (0);
i = 0;
while (s[i])
i++;
return (i);
}

char *ft_strdup(const char *s)
{
char *res;
size_t len;


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


int ft_atoi(const char *nptr)
{
int i;
int sign;
int res;


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


char *ft_strchr(const char *s, int c)
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


int ft_strncmp(const char *s1, const char *s2, size_t n)
{
size_t i;


i = 0;
while (i < n && (s1[i] || s2[i]))
{
if ((unsigned char)s1[i] != (unsigned char)s2[i])
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
i++;
}
return (0);
}


void ft_free(char **arr, int n)
{
int i;


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