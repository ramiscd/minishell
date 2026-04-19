#!/bin/sh

set -e

make -C libft > /dev/null

cc -Wall -Wextra -Werror -Iheaders -Ilibft \
	tests/unit/executor_test.c \
	tests/unit/executor_test_utils.c \
	tests/unit/executor_test_redir.c \
	src/executor/execute_command.c \
	src/redirections/apply_redirs.c \
	src/redirections/restore_stdio.c \
	src/redirections/redir_utils.c \
	src/builtin_functions/builtins.c \
	src/builtin_functions/builtins_utils.c \
	src/builtin_functions/echo.c \
	src/builtin_functions/cd.c \
	src/builtin_functions/cd_utils.c \
	src/builtin_functions/pwd.c \
	src/builtin_functions/env.c \
	src/builtin_functions/export.c \
	src/builtin_functions/unset.c \
	src/builtin_functions/exit.c \
	src/env/env_get.c \
	src/env/env_set.c \
	src/env/env_unset.c \
	src/env/env_utils.c \
	libft/libft.a \
	-o tests/unit/executor_test

./tests/unit/executor_test
