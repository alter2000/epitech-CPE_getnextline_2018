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
#        define READ_SIZE (20)
#    endif // READ_SIZE

typedef struct fd_s {
    int fd;
    int ridx;
    int rbuflen;
    char rbuf[READ_SIZE + 2];
    struct fd_s *next;
} gnl_t;

int my_strlen(char const *);
char *my_strncpy(char *, char const *, int);
void *gib(size_t);

char *get_next_line(int);
char *get_next_delim(int, int);

#endif // GET_NEXT_LINE_H
