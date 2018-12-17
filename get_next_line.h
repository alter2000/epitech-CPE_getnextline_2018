/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** GNL header
*/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef READ_SIZE
#  define READ_SIZE 100
# endif // READ_SIZE

void *regib(char *, int);
char *my_strncpy(char *, char const *, int);
int my_strlen(char *);
void *gib(size_t);

char *get_next_line(int);

#endif // GET_NEXT_LINE_H
