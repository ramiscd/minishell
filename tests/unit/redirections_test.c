/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:00:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 10:00:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <string.h>

static int	test_output_overwrite_restore(void)
{
	t_redir		redir;
	char		buf[8];
	int			saved[2];
	int			fd;
	ssize_t		size;

	unlink("tests/fixtures/redir_out.txt");
	redir.type = REDIR_OUT;
	redir.file = "tests/fixtures/redir_out.txt";
	redir.next = NULL;
	if (apply_redirs(&(t_command){NULL, &redir}, &saved[0], &saved[1]))
		return (1);
	write(1, "abc", 3);
	restore_stdio(saved[0], saved[1]);
	fd = open("tests/fixtures/redir_out.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	size = read(fd, buf, 4);
	if (size != 3 || strncmp(buf, "abc", 3))
		return (1);
	return (close(fd), 0);
}

static int	test_output_append(void)
{
	t_redir		redir;
	char		buf[8];
	int			saved[2];
	int			fd;

	fd = open("tests/fixtures/redir_append.txt", O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (fd < 0 || write(fd, "A", 1) != 1)
		return (1);
	close(fd);
	redir.type = REDIR_APPEND;
	redir.file = "tests/fixtures/redir_append.txt";
	redir.next = NULL;
	if (apply_redirs(&(t_command){NULL, &redir}, &saved[0], &saved[1]))
		return (1);
	write(1, "B", 1);
	restore_stdio(saved[0], saved[1]);
	fd = open("tests/fixtures/redir_append.txt", O_RDONLY);
	if (fd < 0 || read(fd, buf, 2) != 2 || strncmp(buf, "AB", 2))
		return (1);
	return (close(fd), 0);
}

static int	test_input_redir(void)
{
	t_redir		redir;
	char		buf[8];
	int			saved[2];
	int			fd;

	fd = open("tests/fixtures/redir_in.txt", O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (fd < 0 || write(fd, "hello", 5) != 5)
		return (1);
	close(fd);
	redir.type = REDIR_IN;
	redir.file = "tests/fixtures/redir_in.txt";
	redir.next = NULL;
	if (apply_redirs(&(t_command){NULL, &redir}, &saved[0], &saved[1]))
		return (1);
	if (read(0, buf, 5) != 5 || strncmp(buf, "hello", 5))
		return (1);
	restore_stdio(saved[0], saved[1]);
	return (0);
}

static int	test_invalid_input(void)
{
	t_redir		redir;
	int			saved[2];

	redir.type = REDIR_IN;
	redir.file = "tests/fixtures/does_not_exist.txt";
	redir.next = NULL;
	saved[0] = 9;
	saved[1] = 9;
	if (!apply_redirs(&(t_command){NULL, &redir}, &saved[0], &saved[1]))
		return (1);
	if (saved[0] != -1 || saved[1] != -1)
		return (1);
	return (0);
}

int	main(void)
{
	if (test_output_overwrite_restore())
		return (write(2, "test_output_overwrite_restore failed\n", 36), 1);
	if (test_output_append())
		return (write(2, "test_output_append failed\n", 26), 1);
	if (test_input_redir())
		return (write(2, "test_input_redir failed\n", 24), 1);
	if (test_invalid_input())
		return (write(2, "test_invalid_input failed\n", 26), 1);
	write(1, "redirections tests: OK\n", 23);
	return (0);
}
