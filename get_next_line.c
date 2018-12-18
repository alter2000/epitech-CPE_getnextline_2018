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
    file_info->lnbuf = gib(sizeof(char) * READ_SIZE);
    if (!*f) {
        *f = file_info;
    } else {
        for (tmp = *f; tmp && tmp->next; tmp = tmp->next);
        tmp->next = file_info;
    }
    return *f;
}

static void read_till_newline(gnl_t *cur)
{
    for (cur->rbuflen = read(cur->fd, cur->rbuf, READ_SIZE); \
            cur->rbuflen > 0; \
            cur->rbuflen = read(cur->fd, cur->rbuf, READ_SIZE)) {
        cur->rbuf[cur->rbuflen] = 0;
        if (is_in('\n', cur->rbuf))
            break;
        for (int i = 0; cur->rbuf[i]; i++, cur->lnbuflen++)
            cur->lnbuf[cur->lnbuflen] = cur->rbuf[i];
    }
}

char *get_next_line(int fd)
{
    static gnl_t *files;
    gnl_t *cur = ret_file(fd, &files);

    if (fd == -1 || read(cur->fd, cur->rbuf, 0) < 0)
        return 0;
    read_till_newline(cur);
    for (int i = 0; cur->rbuf[i] && cur->rbuf[i] != '\n'; i++, cur->lnbuflen++)
        cur->lnbuf[cur->lnbuflen] = cur->rbuf[i];
    cur->lnbuf[cur->lnbuflen] = 0;
    for (int i = 0; i < cur->rbuflen; i++)
        cur->rbuf[i] = 0;
    return cur->lnbuf;
}
