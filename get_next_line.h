/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL header
*/

#ifndef GET_NEXT_LINE_H
#    define GET_NEXT_LINE_H

#    include <fcntl.h>
#    include <stddef.h>
#    include <stdlib.h>
#    include <sys/types.h>
#    include <unistd.h>

#    ifndef READ_SIZE
#        define READ_SIZE (100)
#    endif // READ_SIZE

typedef struct fd_s {
    int ridx;
    int rbuflen;
    char rbuf[READ_SIZE + 2];
} gnl_t;

char *get_next_line(int);

#endif // GET_NEXT_LINE_H
