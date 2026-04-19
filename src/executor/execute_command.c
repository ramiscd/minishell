/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:20:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 11:20:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static int	wait_and_restore(pid_t pid, int saved_stdin, int saved_stdout,
		t_shell *sh)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		restore_stdio(saved_stdin, saved_stdout);
		sh->error = 1;
		return (1);
	}
	restore_stdio(saved_stdin, saved_stdout);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		sh->error = 0;
		return (0);
	}
	sh->error = 1;
	return (1);
}

static int	execute_external(t_shell *sh, t_command *cmd, int saved_stdin,
		int saved_stdout)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		restore_stdio(saved_stdin, saved_stdout);
		sh->error = 1;
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, sh->envp);
		perror("execve");
		exit(1);
	}
	return (wait_and_restore(pid, saved_stdin, saved_stdout, sh));
}

int	execute_command(t_shell *sh, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!sh)
		return (1);
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		sh->error = 0;
		return (0);
	}
	if (apply_redirs(cmd, &saved_stdin, &saved_stdout))
	{
		sh->error = 1;
		return (1);
	}
	if (is_builtin(cmd))
	{
		run_builtin_parent(sh, cmd);
		restore_stdio(saved_stdin, saved_stdout);
		return ((sh->error != 0));
	}
	return (execute_external(sh, cmd, saved_stdin, saved_stdout));
}
