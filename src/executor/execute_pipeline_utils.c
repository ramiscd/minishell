/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:00:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_child_redirs(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (apply_redirs(cmd, &saved_stdin, &saved_stdout))
		return (1);
	if (saved_stdin >= 0)
		close(saved_stdin);
	if (saved_stdout >= 0)
		close(saved_stdout);
	return (0);
}

static void	exec_child_command(t_shell *sh, t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(1);
	if (is_builtin(cmd))
	{
		run_builtin_child(sh, cmd);
		if (sh->error)
			exit(1);
		exit(0);
	}
	execve(cmd->argv[0], cmd->argv, sh->envp);
	perror("execve");
	exit(1);
}

int	pipeline_child_setup(t_shell *sh, t_command *cmd)
{
	if (apply_child_redirs(cmd))
		exit(1);
	exec_child_command(sh, cmd);
	return (1);
}
