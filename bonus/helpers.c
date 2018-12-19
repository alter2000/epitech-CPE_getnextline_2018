
#include "get_next_line.h"

void *gib(size_t n)
{
    char *p = 0;

    if (n <= 0)
        return 0;
    while (!p)
        p = malloc(n);
    for (size_t i = 0; i < n; i++)
        p[i] = 0;
    return p;
}

int my_strlen(char const *s)
{
    int i = 0;

    while (s && s[i])
        i++;
    return i;
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (!src || n < 1)
        return 0;
    for (; src[i] && i < n; i++)
        dest[i] = src[i];
    if (i > n)
        dest[i] = '\0';
    return dest;
}
