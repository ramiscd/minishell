/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:03 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

static int	count_cmds(t_command *cmds)
{
	int	n;

	n = 0;
	while (cmds)
	{
		n++;
		cmds = cmds->next;
	}
	return (n);
}

static void	close_all_pipes(int *pipe_fds, int n)
{
	int	i;

	i = 0;
	while (i < (n - 1) * 2)
	{
		close(pipe_fds[i]);
		i++;
	}
}

static void	run_child(t_shell *sh, t_command *cmd, int *pipe_fds, int i, int n)
{
	char	*path;
	int		saved_stdin;
	int		saved_stdout;

	if (i > 0)
		dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
	if (i < n - 1)
		dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close_all_pipes(pipe_fds, n);
	apply_redirs(cmd, &saved_stdin, &saved_stdout);
	if (is_builtin(cmd))
	{
		run_builtin_child(sh, cmd);
		exit((unsigned char)sh->error);
	}
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

void	execute_pipeline(t_shell *sh, t_command *head)
{
	int			n;
	int			*pipe_fds;
	pid_t		*pids;
	t_command	*cmd;
	int			i;
	int			status;

	n = count_cmds(head);
	if (n == 1)
	{
		execute_command(sh, head);
		return ;
	}
	pipe_fds = malloc(sizeof(int) * (n - 1) * 2);
	pids = malloc(sizeof(pid_t) * n);
	if (!pipe_fds || !pids)
	{
		free(pipe_fds);
		free(pids);
		sh->error = 1;
		return ;
	}
	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			free(pipe_fds);
			free(pids);
			sh->error = 1;
			return ;
		}
		i++;
	}
	cmd = head;
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			close_all_pipes(pipe_fds, n);
			free(pipe_fds);
			free(pids);
			sh->error = 1;
			return ;
		}
		if (pids[i] == 0)
			run_child(sh, cmd, pipe_fds, i, n);
		cmd = cmd->next;
		i++;
	}
	close_all_pipes(pipe_fds, n);
	status = 0;
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		sh->error = (char)WEXITSTATUS(status);
	else
		sh->error = 1;
	free(pipe_fds);
	free(pids);
}
