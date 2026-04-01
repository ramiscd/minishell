NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	src/main.c \
	src/lexer/lexer.c \
	src/lexer/lexer_utils.c \
	src/lexer/token_add.c \
	src/lexer/token_create.c \
	src/parser/parser.c \
	src/parser/parser_utils.c \
	src/parser/builder.c

OBJ = $(SRC:.c=.o)

INCLUDES = -Iheaders

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all