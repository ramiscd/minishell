/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:20:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

static int	fork_failed(char *path, int sin, int sout, t_shell *sh)
{
	perror("fork");
	free(path);
	restore_stdio(sin, sout);
	sh->error = 1;
	return (1);
}

static void	exec_child(char *path, t_command *cmd, t_shell *sh)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, cmd->argv, sh->envp);
	perror(path);
	free(path);
	exit(127);
}

static int	wait_and_restore(pid_t pid, int sin, int sout, t_shell *sh)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		restore_stdio(sin, sout);
		sh->error = 1;
		return (1);
	}
	restore_stdio(sin, sout);
	if (WIFEXITED(status))
		sh->error = (char)WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->error = (char)(128 + WTERMSIG(status));
	else
		sh->error = 1;
	return (sh->error != 0);
}

static int	execute_external(t_shell *sh, t_command *cmd, int sin, int sout)
{
	char	*path;
	pid_t	pid;

	path = resolve_path(sh, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		restore_stdio(sin, sout);
		sh->error = (char)127;
		return (127);
	}
	pid = fork();
	if (pid < 0)
		return (fork_failed(path, sin, sout, sh));
	if (pid == 0)
		exec_child(path, cmd, sh);
	free(path);
	return (wait_and_restore(pid, sin, sout, sh));
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
