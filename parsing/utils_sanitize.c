#include "../include/cub3d.h"



static int has_space(char *s)
{
int i;


i = 0;
while (s && s[i])
{
if (s[i] == ' ')
return (1);
i++;
}
return (0);
}


char **sanitize(char **string)
{
int i;
int count;
char **tmp;


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