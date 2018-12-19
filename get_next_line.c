/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL implementation
*/

#include "get_next_line.h"

static int my_strlen(char const *s)
{
    int i = 0;

    while (s && s[i])
        i++;
    return i;
}

static char *my_strncpy(char *dest, char const *src, int n)
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

static char *append(char *lnbuf, int n, gnl_t *f)
{
    int oldlen = my_strlen(lnbuf);
    char *newlen = malloc((oldlen + n + 1) * sizeof(*newlen));

    my_strncpy(newlen, lnbuf, oldlen);
    newlen[oldlen + n] = 0;
    my_strncpy(newlen + oldlen, f->rbuf + f->ridx, n);
    if (lnbuf)
        free(lnbuf);
    f->ridx = f->ridx + (n + 1);
    return (newlen);
}

char *get_next_line(const int fd)
{
    static gnl_t f;
    static int readret = 0;
    int n = 0;
    char *lnbuf = 0;

    while (1) {
        if (readret <= f.ridx) {
            f.ridx = 0;
            n = 0;
            readret = read(fd, f.rbuf, READ_SIZE);
            if (readret <= 0)
                return (readret == 0) ? lnbuf : 0;
        }
        if (f.rbuf[f.ridx + n] == '\n')
            return append(lnbuf, n, &f);
        if (f.ridx + n == readret - 1)
            lnbuf = append(lnbuf, n + 1, &f);
        n++;
    }
}
