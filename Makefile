##
## EPITECH PROJECT, 2018
## CPool_Day07_2018
## File description:
## standard makefile
##

all: tests_run

clean:
	@rm -f $(shell find . -name '*.gc*') $(shell find . -name 'vgcore.*')

fclean: clean
	@rm -f unit_tests

re: fclean

tests_run: tests
	gcc -o unit_tests ./tests/gnl.c ./get_next_line.c \
		-lcriterion --coverage && ./unit_tests

.PHONY: all clean fclean re tests_run
