/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL implementation
*/

#include "get_next_line.h"

static char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (!src || n < 1)
        return 0;
    for (; src[i] && i < n; i++)
        dest[i] = src[i];
    if (i > n)
        dest[i] = 0;
    return dest;
}

static char *append(char *lnbuf, int n, gnl_t *f)
{
    int i = 0;
    int oldlen;
    char *newlen;

    while (lnbuf && lnbuf[i])
        i++;
    oldlen = i;
    newlen = malloc((oldlen + n + 1) * sizeof(*newlen));
    while (!newlen)
        newlen = malloc((oldlen + n + 1) * sizeof(*newlen));
    my_strncpy(newlen, lnbuf, oldlen);
    newlen[oldlen + n] = 0;
    my_strncpy(newlen + oldlen, f->rbuf + f->ridx, n);
    if (lnbuf)
        free(lnbuf);
    f->ridx += n + 1;
    return newlen;
}

static void reread(gnl_t *f, int *n, int *readret, int fd)
{
    f->ridx = 0;
    *n = 0;
    *readret = read(fd, f->rbuf, (int)READ_SIZE);
}

char *get_next_line(const int fd)
{
    static gnl_t f;
    static int readret = 0;
    int n = 0;
    char *lnbuf = 0;

    if ((int)READ_SIZE < 1)
        return 0;
    while (1) {
        if (readret <= f.ridx) {
            reread(&f, &n, &readret, fd);
            if (readret <= 0)
                return (readret == 0) ? lnbuf : 0;
        }
        if (f.rbuf[f.ridx + n] == '\n' || f.rbuf[f.ridx + n] == EOF)
            return append(lnbuf, n, &f);
        if (f.ridx + n == readret - 1)
            lnbuf = append(lnbuf, n + 1, &f);
        n++;
    }
}
