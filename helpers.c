
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

void *regib(char *s, int extra)
{
    int oldsize = my_strlen(s);
    int newsize = 1 + oldsize + extra;
    char *newstr = gib(sizeof(char) * (newsize + 2));
    int i = 0;

    if (!s || oldsize < 1)
        return 0;
    for (; s[i]; i++)
        newstr[i] = s[i];
    newstr[i] = 0;
    free(s);
    return newstr;
}

int my_strlen(char *s)
{
    int i = 0;

    while (s && s[i])
        i++;
    return i;
}

char *my_strncat(char *dest, char const *src, int n)
{
    int i = 0;
    char *newdest = regib(dest, my_strlen(dest));
    char *len = newdest + my_strlen(dest);

    for (; src[i] && i < n; i++)
        len[i] = src[i];
    len[i] = 0;
    return newdest;
}

int is_in(char const elem, char const *set)
{
    for (unsigned int i = 0; set[i]; i++)
        if (set[i] == elem)
            return 1;
    return 0;
}
