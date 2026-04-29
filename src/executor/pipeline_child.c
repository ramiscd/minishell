/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

void	close_all_pipes(int *pipe_fds, int n)
{
	int	i;

	i = 0;
	while (i < (n - 1) * 2)
	{
		close(pipe_fds[i]);
		i++;
	}
}

static void	exec_external(t_shell *sh, t_command *cmd)
{
	char	*path;

	path = resolve_path(sh, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	perror(path);
	free(path);
	exit(127);
}

static void	run_child(t_shell *sh, t_command *cmd, t_child_data *d)
{
	int		saved_stdin;
	int		saved_stdout;

	if (d->i > 0)
		dup2(d->pipe_fds[(d->i - 1) * 2], STDIN_FILENO);
	if (d->i < d->n - 1)
		dup2(d->pipe_fds[d->i * 2 + 1], STDOUT_FILENO);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close_all_pipes(d->pipe_fds, d->n);
	apply_redirs(cmd, &saved_stdin, &saved_stdout);
	if (is_builtin(cmd))
	{
		run_builtin_child(sh, cmd);
		exit((unsigned char)sh->error);
	}
	exec_external(sh, cmd);
}

int	do_fork(t_shell *sh, t_command *cmd, t_child_data *d, pid_t *pids)
{
	pids[d->i] = fork();
	if (pids[d->i] < 0)
	{
		perror("fork");
		close_all_pipes(d->pipe_fds, d->n);
		free(pids);
		return (sh->error = 1, 0);
	}
	if (pids[d->i] == 0)
		run_child(sh, cmd, d);
	return (1);
}

void	wait_children(pid_t *pids, t_child_data *d)
{
	d->i = 0;
	while (d->i < d->n)
	{
		waitpid(pids[d->i], &d->last_status, 0);
		d->i++;
	}
}
