/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:06:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 18:06:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_apply_node(t_redir *redir);

static int	save_stdio(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
	{
		perror("dup");
		return (1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout < 0)
	{
		perror("dup");
		close(*saved_stdin);
		*saved_stdin = -1;
		return (1);
	}
	return (0);
}

int	apply_redirs(t_command *cmd, int *saved_stdin, int *saved_stdout)
{
	t_redir	*redir;

	if (!saved_stdin || !saved_stdout)
		return (1);
	*saved_stdin = -1;
	*saved_stdout = -1;
	if (!cmd || !cmd->redirs)
		return (0);
	if (save_stdio(saved_stdin, saved_stdout))
		return (1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir_apply_node(redir))
		{
			restore_stdio(*saved_stdin, *saved_stdout);
			*saved_stdin = -1;
			*saved_stdout = -1;
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
