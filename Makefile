# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 19:46:51 by rdamasce          #+#    #+#              #
#    Updated: 2026/04/20 00:00:00 by rdamasce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iheaders -Ilibft
LIBFT = libft/libft.a

SRC = \
	src/main.c \
	src/lexer/lexer.c \
	src/lexer/lexer_utils.c \
	src/lexer/token_add.c \
	src/lexer/token_create.c \
	src/parser/parser.c \
	src/parser/parser_utils.c \
	src/parser/builder.c \
	src/executor/execute_command.c \
	src/builtin_functions/builtins.c \
	src/builtin_functions/builtins_utils.c \
	src/builtin_functions/cd.c \
	src/builtin_functions/cd_utils.c \
	src/builtin_functions/echo.c \
	src/builtin_functions/env.c \
	src/builtin_functions/exit.c \
	src/builtin_functions/export.c \
	src/builtin_functions/pwd.c \
	src/builtin_functions/unset.c \
	src/env/env_get.c \
	src/env/env_set.c \
	src/env/env_unset.c \
	src/env/env_utils.c \
	src/redirections/apply_redirs.c \
	src/redirections/redir_utils.c \
	src/redirections/restore_stdio.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
