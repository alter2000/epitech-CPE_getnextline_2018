/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL implementation
*/

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char buf[READ_SIZE] = {0};
    char *res = gib(READ_SIZE);
    char *tmp;
    int ret = (fd) ? read(fd, buf, READ_SIZE) : 0;

    if (!fd)
        return 0;
    while (ret > 0) {
        buf[ret] = 0;
    }
    return res;
}

gnl_t *mkstruct(gnl_t *former, int fd)
{
    gnl_t *file_info = gib(sizeof(*file_info));

    file_info->fd = fd;
    file_info->lnbuflen = 0;
    file_info->nextch = 0;
    file_info->rbuflen = read(fd, file_info->rbuf, READ_SIZE);
    file_info->rbufidx = 0;
    file_info->next = former;
    return file_info;
}

