/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL implementation
*/

#include <stdio.h>
#include "get_next_line.h"

static gnl_t *ret_file(int const fd, gnl_t **f)
{
    gnl_t *tmp;
    gnl_t *file_info;

    for (tmp = *f; tmp; tmp = tmp->next)
        if (tmp->fd == fd)
            return tmp;
    file_info = gib(sizeof(*file_info));
    file_info->fd = fd;
    if (!*f) {
        *f = file_info;
    } else {
        for (tmp = *f; tmp && tmp->next; tmp = tmp->next);
        tmp->next = file_info;
    }
    return file_info;
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
    f->ridx += n + 1;
    return (newlen);
}

char *get_next_delim(const int fd, const int ch)
{
    static gnl_t *all_f;
    static int readret = 0;
    gnl_t *f = ret_file(fd, &all_f);
    int n = 0;
    char *lnbuf = 0;

    while (1) {
        if (readret <= f->ridx) {
            f->ridx = 0;
            n = 0;
            readret = read(fd, f->rbuf, READ_SIZE);
            if (readret <= 0)
                return (readret == 0) ? lnbuf : 0;
        }
        if (f->rbuf[f->ridx + n] == ch)
            return append(lnbuf, n, f);
        if (f->ridx + n == readret - 1)
            lnbuf = append(lnbuf, n + 1, f);
        n++;
    }
}

char *get_next_line(const int fd)
{
    return get_next_delim(fd, '\n');
}
