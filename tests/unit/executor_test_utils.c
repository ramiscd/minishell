/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_test_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:25:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 11:25:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *sh, char **envp)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->envp = envp;
}

static int	start_capture(int *saved_stdout, int pipefd[2])
{
	if (pipe(pipefd) < 0)
		return (1);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout < 0)
		return (close(pipefd[0]), close(pipefd[1]), 1);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(*saved_stdout), close(pipefd[0]), close(pipefd[1]), 1);
	close(pipefd[1]);
	return (0);
}

static int	end_capture(int saved_stdout, int read_fd, char *buf, size_t size)
{
	ssize_t	read_size;

	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		return (close(saved_stdout), close(read_fd), 1);
	close(saved_stdout);
	read_size = read(read_fd, buf, size - 1);
	close(read_fd);
	if (read_size < 0)
		return (1);
	buf[read_size] = '\0';
	return (0);
}

int	run_capture_command(t_shell *sh, t_command *cmd, char *expect)
{
	int		saved_stdout;
	int		pipefd[2];
	char	out[64];

	if (start_capture(&saved_stdout, pipefd))
		return (1);
	if (execute_command(sh, cmd))
		return (end_capture(saved_stdout, pipefd[0], out, sizeof(out)), 1);
	if (end_capture(saved_stdout, pipefd[0], out, sizeof(out)))
		return (1);
	if (sh->error || ft_strncmp(out, expect, 63))
		return (1);
	return (0);
}

int	test_redir_failure(void)
{
	t_shell		sh;
	t_command	cmd;
	t_redir		redir;
	char		*envp[1];
	char		*argv[2];

	envp[0] = NULL;
	init_shell(&sh, envp);
	argv[0] = "/bin/cat";
	argv[1] = NULL;
	redir.type = REDIR_IN;
	redir.file = "tests/fixtures/not_found_input.txt";
	redir.next = NULL;
	cmd.argv = argv;
	cmd.redirs = &redir;
	if (!execute_command(&sh, &cmd) || !sh.error)
		return (1);
	return (0);
}
