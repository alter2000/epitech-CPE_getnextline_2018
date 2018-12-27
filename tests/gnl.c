/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** all tests for get_next_line
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>

#include "../get_next_line.h"

Test(get_next_line, read_line_3)
{
    int fd = open("./tests/blag.md", O_RDONLY);

    cr_expect_str_eq(get_next_line(fd), "# Ligaturizer #");
    cr_expect_str_eq(get_next_line(fd), "");
    cr_expect_str_eq(get_next_line(fd), "![](images/banner.png)");
    close(fd);
}

Test(get_next_line, loop)
{
    int fd = open("tests/blag.md", O_RDONLY);

    for (int i = 0; i < 6; i++)
        get_next_line(fd);

    cr_expect_str_eq(get_next_line(fd), \
        "This script copies the ligatures (glyphs and rendering information) "
        "from [Fira Code](https://github.com/tonsky/FiraCode) into any other "
        "TrueType or OpenType font. (Note that the ligatures are "
        "scale-corrected, but otherwise copied as is from Fira Code; it "
        "doesn't create new ligature graphics based on the font you're "
        "modifying.). You need a l o n g b o a r d to make a l o n g l i n e");
    close(fd);
}

Test(get_next_line, second_file)
{
    int fd = open("tests/blag.md", O_RDONLY);
    int fd2 = open("tests/gnl.c", O_RDONLY);

    for (int i = 0; i < 6; i++)
        get_next_line(fd);
    cr_expect_str_eq(get_next_line(fd), \
        "This script copies the ligatures (glyphs and rendering information) "
        "from [Fira Code](https://github.com/tonsky/FiraCode) into any other "
        "TrueType or OpenType font. (Note that the ligatures are "
        "scale-corrected, but otherwise copied as is from Fira Code; it "
        "doesn't create new ligature graphics based on the font you're "
        "modifying.). You need a l o n g b o a r d to make a l o n g l i n e");
    cr_expect_str_eq(get_next_line(fd2), "/*");
    close(fd);
    close(fd2);
}

Test(get_next_line, invalid_fd)
{
    char *p = get_next_line(-1);

    cr_expect_eq(p, 0);
}

Test(get_next_line, empty)
{
    int f = open("./tests/empty", O_RDONLY);
    char *p = get_next_line(f);

    cr_expect_eq(p, 0);
    close(f);
}
