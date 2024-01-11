CC=gcc
CFLAGS=-Wextra -Werror -Wall
LIBS=-lreadline libft/libft.a
SRC=parsing_cmd.c\
		parsing_inout.c\
		parsing_tools.c\
		parsing.c\
		tools_struct.c\
		struct_init.c\
		handle_error.c\
		checker_here.c\
		checker_quote.c\
		execute_v2.c
OBJ=$(SRC:.c=.o)
EXEC=mini_shell

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all
