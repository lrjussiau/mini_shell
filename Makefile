CC=gcc
CFLAGS=-Wextra -Werror -Wall -I/Users/$(shell whoami)/.brew/opt/readline/include -g
LDFLAGS=-L/Users/$(shell whoami)/.brew/opt/readline/lib
LIBS=-lreadline libft/libft.a
SRC=parsing_cmd.c \
    mini_shell.c \
    parsing_inout.c \
    parsing_tools.c \
    parsing.c \
    tools_struct.c \
    struct_init.c \
    handle_error.c \
    checker_here.c \
    checker_quote.c \
    execute.c \
    builtins.c \
    builtins_utils.c \
    smart_split.c \
    env_var_check.c \
    env_var_cmd.c \
    echo_cmd.c \
    input_output.c \
    bin_exec.c \
    fd_tab.c \
    exec_utils.c \
	signal.c \
    cd_cmd.c \
    parsing_dollar.c \
    origin_handler.c
OBJ=$(SRC:.c=.o)
EXEC=mini_shell

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all
