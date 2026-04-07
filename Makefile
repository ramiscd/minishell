# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 19:46:51 by rdamasce          #+#    #+#              #
#    Updated: 2026/04/07 20:16:17 by rdamasce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iheaders

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

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re