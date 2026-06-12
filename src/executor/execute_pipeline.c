/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:00:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	pipeline_child_setup(t_shell *sh, t_command *cmd);

static pid_t	fork_first_child(t_shell *sh, t_command *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd[1]);
		pipeline_child_setup(sh, cmd);
	}
	return (pid);
}

static pid_t	fork_second_child(t_shell *sh, t_command *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd[0]);
		pipeline_child_setup(sh, cmd);
	}
	return (pid);
}

static int	wait_pipeline(t_shell *sh, pid_t first_pid, pid_t second_pid)
{
	int	first_status;
	int	second_status;

	first_status = 0;
	second_status = 0;
	if (waitpid(first_pid, &first_status, 0) < 0)
		return (perror("waitpid"), sh->error = 1, 1);
	if (waitpid(second_pid, &second_status, 0) < 0)
		return (perror("waitpid"), sh->error = 1, 1);
	if (WIFEXITED(first_status) && WEXITSTATUS(first_status) == 0
		&& WIFEXITED(second_status) && WEXITSTATUS(second_status) == 0)
	{
		sh->error = 0;
		return (0);
	}
	sh->error = 1;
	return (1);
}

int	execute_pipeline(t_shell *sh, t_command *cmd)
{
	int		fd[2];
	pid_t	first_pid;
	pid_t	second_pid;

	if (!sh || !cmd || !cmd->next)
		return (1);
	if (pipe(fd) < 0)
		return (perror("pipe"), sh->error = 1, 1);
	first_pid = fork_first_child(sh, cmd, fd);
	if (first_pid < 0)
		return (close(fd[0]), close(fd[1]), sh->error = 1, 1);
	second_pid = fork_second_child(sh, cmd->next, fd);
	close(fd[0]);
	close(fd[1]);
	if (second_pid < 0)
		return (waitpid(first_pid, NULL, 0), sh->error = 1, 1);
	return (wait_pipeline(sh, first_pid, second_pid));
}
