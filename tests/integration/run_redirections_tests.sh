#!/bin/sh

set -e

cc -Wall -Wextra -Werror -Iheaders -Ilibft \
	tests/unit/redirections_test.c \
	src/redirections/apply_redirs.c \
	src/redirections/restore_stdio.c \
	src/redirections/redir_utils.c \
	-o tests/unit/redirections_test

./tests/unit/redirections_test
