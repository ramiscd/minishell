/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

void	close_all_pipes(int *pipe_fds, int n);
int		do_fork(t_shell *sh, t_command *cmd, t_child_data *d, pid_t *pids);
void	wait_children(pid_t *pids, t_child_data *d);

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

static int	open_pipes(t_shell *sh, t_child_data *d)
{
	int	i;

	i = 0;
	while (i < d->n - 1)
	{
		if (pipe(d->pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			free(d->pipe_fds);
			sh->error = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	fork_children(t_shell *sh, t_command *head, t_child_data *d)
{
	t_command	*cmd;
	pid_t		*pids;

	pids = malloc(sizeof(pid_t) * d->n);
	if (!pids)
		return (sh->error = 1, 0);
	cmd = head;
	d->i = 0;
	while (cmd)
	{
		if (!do_fork(sh, cmd, d, pids))
			return (0);
		cmd = cmd->next;
		d->i++;
	}
	close_all_pipes(d->pipe_fds, d->n);
	wait_children(pids, d);
	free(pids);
	return (1);
}

void	execute_pipeline(t_shell *sh, t_command *head)
{
	t_child_data	d;

	d.n = count_cmds(head);
	if (d.n == 1)
	{
		execute_command(sh, head);
		return ;
	}
	d.pipe_fds = malloc(sizeof(int) * (d.n - 1) * 2);
	if (!d.pipe_fds)
		return ((void)(sh->error = 1));
	if (!open_pipes(sh, &d))
		return ;
	d.last_status = 0;
	if (fork_children(sh, head, &d))
	{
		if (WIFEXITED(d.last_status))
			sh->error = (unsigned char)WEXITSTATUS(d.last_status);
		else
			sh->error = 1;
	}
	free(d.pipe_fds);
}
