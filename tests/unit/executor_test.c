/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:25:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 11:25:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *sh, char **envp);
int		run_capture_command(t_shell *sh, t_command *cmd, char *expect);
int		test_redir_failure(void);
int		test_redir_output(void);

static int	test_builtin_echo(void)
{
	t_shell		sh;
	t_command	cmd;
	char		*envp[1];
	char		*argv[3];

	envp[0] = NULL;
	init_shell(&sh, envp);
	argv[0] = "echo";
	argv[1] = "hello";
	argv[2] = NULL;
	cmd.argv = argv;
	cmd.redirs = NULL;
	if (run_capture_command(&sh, &cmd, "hello\n"))
		return (1);
	return (0);
}

static int	test_external_echo(void)
{
	t_shell		sh;
	t_command	cmd;
	char		*envp[2];
	char		*argv[3];

	envp[0] = "PATH=/usr/bin:/bin";
	envp[1] = NULL;
	init_shell(&sh, envp);
	argv[0] = "/bin/echo";
	argv[1] = "hello";
	argv[2] = NULL;
	cmd.argv = argv;
	cmd.redirs = NULL;
	if (run_capture_command(&sh, &cmd, "hello\n"))
		return (1);
	return (0);
}

static int	test_invalid_command(void)
{
	t_shell		sh;
	t_command	cmd;
	char		*envp[1];
	char		*argv[2];

	envp[0] = NULL;
	init_shell(&sh, envp);
	argv[0] = "nonexistent_command_executor";
	argv[1] = NULL;
	cmd.argv = argv;
	cmd.redirs = NULL;
	if (!execute_command(&sh, &cmd) || !sh.error)
		return (1);
	return (0);
}

int	main(void)
{
	if (test_builtin_echo())
		return (write(2, "test_builtin_echo failed\n", 24), 1);
	if (test_external_echo())
		return (write(2, "test_external_echo failed\n", 25), 1);
	if (test_redir_output())
		return (write(2, "test_redir_output failed\n", 25), 1);
	if (test_invalid_command())
		return (write(2, "test_invalid_command failed\n", 28), 1);
	if (test_redir_failure())
		return (write(2, "test_redir_failure failed\n", 26), 1);
	write(1, "executor tests: OK\n", 19);
	return (0);
}
