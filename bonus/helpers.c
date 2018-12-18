
#include "get_next_line.h"

static int my_strlen(char const *s)
{
    int i = 0;

    while (s && s[i])
        i++;
    return i;
}

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

char *my_strmerge(char *dest, char const *src)
{
    int i;
    int len_1 = my_strlen(src);
    int len_2 = my_strlen(dest);
    char *newstr = gib(sizeof(char) * (len_1 + len_2));

    if (!src || !dest)
        return 0;
    for (i = 0; i < len_1; i++)
        newstr[i] = src[i];
    for (int j = 0; j < len_2; j++)
        newstr[i] = dest[j];
    return newstr;
}

int is_in(char const elem, char const *set)
{
    for (unsigned int i = 0; set[i]; i++)
        if (set[i] == elem)
            return 1;
    return 0;
}
