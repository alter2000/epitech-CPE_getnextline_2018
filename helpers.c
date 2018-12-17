
#include "get_next_line.h"

void *gib(size_t n)
{
    char *p;

    if (n <= 0)
        return 0;
    while (!p)
        p = malloc(n);
    for (size_t i = 0; i < n; i++)
        p[i] = 0;
    return p;
}

int my_strlen(char *s)
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

void *regib(char *s, int extra)
{
    char *newstr = 0;
    int oldsize = my_strlen(s);
    int newsize = 1 + oldsize + extra;

    while (!newstr)
        newstr = malloc(sizeof(char) * (newsize + 2));
    newstr = my_strncpy(newstr, s, oldsize);
    free(s);
    return newstr;
}
