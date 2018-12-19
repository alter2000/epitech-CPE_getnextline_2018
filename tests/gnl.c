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

int fd =  -1;
int fd2 =  -1;

void  open_file(void)
{
    fd = open("tests/blag.md", O_RDONLY);
    cr_redirect_stdout();
}

void open_other_file(void)
{
    fd = open("tests/blag.md", O_RDONLY);
    fd2 = open("tests/keks", O_RDONLY);
    cr_redirect_stdout();
}

void close_other_file(void)
{
    if (fd !=  -1)
        close(fd);
    fd = -1;
    if (fd2 != -1)
        close(fd2);
    fd2 = -1;
}

void close_file(void)
{
    if (fd !=  -1)
        close(fd);
    fd = -1;
}

Test(get_next_line, read_line_3, .init = open_file, .fini = close_file)
{
    cr_expect_str_eq(get_next_line(fd), "# Ligaturizer #");
    cr_expect_str_eq(get_next_line(fd), "");
    cr_expect_str_eq(get_next_line(fd), "![](images/banner.png)");
}

Test(get_next_line, loop, .init = open_file, .fini = close_file)
{
    for (int i = 0; i < 6; i++)
        get_next_line(fd);

    cr_expect_str_eq(get_next_line(fd), \
        "This script copies the ligatures (glyphs and rendering information) "
        "from [Fira Code](https://github.com/tonsky/FiraCode) into any other "
        "TrueType or OpenType font. (Note that the ligatures are "
        "scale-corrected, but otherwise copied as is from Fira Code; it "
        "doesn't create new ligature graphics based on the font you're "
        "modifying.)");
}

Test(get_next_line, second_file, \
        .init = open_other_file, .fini = close_other_file)
{
    for (int i = 0; i < 6; i++)
        get_next_line(fd);
    cr_expect_str_eq(get_next_line(fd), \
        "This script copies the ligatures (glyphs and rendering information) "
        "from [Fira Code](https://github.com/tonsky/FiraCode) into any other "
        "TrueType or OpenType font. (Note that the ligatures are "
        "scale-corrected, but otherwise copied as is from Fira Code; it "
        "doesn't create new ligature graphics based on the font you're "
        "modifying.)");
    cr_expect_str_eq(get_next_line(fd2), "yet another file to test switching");
}
