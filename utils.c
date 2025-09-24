#include "cub3d.h"

static int word_count(const char *str, char c);
static char *fill_word(const char *str, int start, int end);
static void ft_initiate_vars(size_t *i, int *j, int *s_word);

int ft_isspace(int c)
{
    return ((c >= 9 && c <= 13) || c == ' ');
}

char **ft_split(const char *s, char c)
{
    char **res;
    size_t i;
    int j;
    int s_word;
    
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
                return (ft_free(res, j));
            s_word = -1;
            j++;
        }
        i++;
    }
    return (res);
}


static void ft_initiate_vars(size_t *i, int *j, int *s_word)
{
    *i = 0;
    *j = 0;
    *s_word = -1;
}

void ft_free(char **strs, int count)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}

static char *fill_word(const char *str, int start, int end)
{
    char *word;
    int i;
    
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

static int word_count(const char *str, char c)
{
    int count;
    int x;
    
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

int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    
    while (ft_isspace(*str))
        str++;
        
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;
    size_t total_size;
    
    total_size = count * size;
    ptr = malloc(total_size);
    if (ptr)
        memset(ptr, 0, total_size);
    return ptr;
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    
    i = 0;
    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
        
    if (i == n)
        return 0;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;
    
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
        
    return i;
}

int rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

int check_newline(char *s)
{
    if (!s)
        return 0;
    while (*s)
    {
        if (*s == '\n')
            return 1;
        s++;
    }
    return 0;
}