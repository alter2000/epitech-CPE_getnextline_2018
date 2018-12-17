/*
** EPITECH PROJECT, 2018
** muhlib
** File description:
** memset(3) clone
*/

#include "my.h"

void *my_memset(char *s, char ch, size_t n)
{
    if (!s)
        return 0;
    for (size_t i = 0; i < n; i++)
        s[i] = ch;
    return s;
}

void *gib(size_t n)
{
    void *p = malloc(n);

    while (!p)
        p = malloc(n);
    return my_memset(p, 0, n);
}
