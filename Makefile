CC=clang
CFLAGS=-Wall -Wextra -Werror -g3 -fsanitize=address

all:
	$(CC) $(CFLAGS) my_readline.c -o my_readline

clean:
	rm -f my_readline

fclean: clean
