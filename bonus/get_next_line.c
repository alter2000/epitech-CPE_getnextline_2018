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
    return *f;
}

static void read_till_newline(gnl_t *cur, char *lnbuf, int lnbuflen, char *buf)
{
    for (int i = 0; i < cur->rbuflen; i++)
        lnbuf[i] = cur->rbuf[i];
    for (int i = 0; i < cur->rbuflen; i++)
        cur->rbuf[i] = 0;
    cur->rbuflen = 0;
    for (int i = 0; buf[i] && buf[i] != '\n'; i++)
        lnbuf[lnbuflen] = buf[i];
    for (cur->rbuflen = read(cur->fd, buf, READ_SIZE); \
            cur->rbuflen > 0; \
            cur->rbuflen = read(cur->fd, buf, READ_SIZE)) {
        buf[cur->rbuflen] = 0;
        if (is_in('\n', buf))
            return;
        for (int i = 0; buf[i]; i++, lnbuflen++)
            lnbuf[lnbuflen] = buf[i];
    }
}

char *get_next_line(int fd)
{
    char buf[READ_SIZE + 1] = {0};
    char *lnbuf = gib(sizeof(char) * READ_SIZE);
    static gnl_t *files;
    gnl_t *cur = ret_file(fd, &files);
    int i = 0;
    int lnbuflen = 0;

    if (fd == -1 || read(cur->fd, buf, 0) < 0)
        return 0;
    read_till_newline(cur, lnbuf, lnbuflen, buf);
    for (; buf[i] && buf[i] != '\n'; i++, lnbuflen++)
        lnbuf[lnbuflen] = buf[i];
    lnbuf[lnbuflen] = 0;
    while (buf[i] && buf[i] != '\n') i++;
    for (; i < cur->rbuflen; buf[i++] = 0)
        cur->rbuf[i] = buf[i];
    return lnbuf;
}

int main(void)
{
    int f = open("./get_next_line.c", O_RDONLY);
    char *s1 = get_next_line(f);
    char *s2 = get_next_line(f);

    for (int i = 0; s1[i]; i++)
        write(1, s1 + i, 1);
    write(1, "\n", 1);
    for (int i = 0; s2[i]; i++)
        write(1, s2 + i, 1);
}
