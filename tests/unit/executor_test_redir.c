/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_test_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:25:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 11:25:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <string.h>

void	init_shell(t_shell *sh, char **envp);

static int	check_output_file(void)
{
	char	buf[16];
	int		fd;
	ssize_t	size;

	fd = open("tests/fixtures/executor_out.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	size = read(fd, buf, 15);
	close(fd);
	if (size != 6)
		return (1);
	buf[size] = '\0';
	if (strcmp(buf, "hello\n"))
		return (1);
	return (0);
}

int	test_redir_output(void)
{
	t_shell		sh;
	t_command	cmd;
	t_redir		redir;
	char		*envp[1];
	char		*argv[3];

	unlink("tests/fixtures/executor_out.txt");
	envp[0] = NULL;
	init_shell(&sh, envp);
	argv[0] = "echo";
	argv[1] = "hello";
	argv[2] = NULL;
	redir.type = REDIR_OUT;
	redir.file = "tests/fixtures/executor_out.txt";
	redir.next = NULL;
	cmd.argv = argv;
	cmd.redirs = &redir;
	if (execute_command(&sh, &cmd) || sh.error)
		return (1);
	if (check_output_file())
		return (1);
	return (0);
}
