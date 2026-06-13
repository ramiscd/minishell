/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/06/13 11:15:50 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static char	*expand_line(char *line, t_redir *redir, t_shell *sh)
{
	if (redir->quoted)
		return (ft_strdup(line));
	return (expand_heredoc_line(line, sh));
}

static int	next_line(char **line, t_shell *sh)
{
	*line = heredoc_readline();
	if (heredoc_interrupted(sh))
		return (1);
	return (0);
}

static int	fill_heredoc(int *pfd, t_redir *redir, t_shell *sh)
{
	char	*line;
	char	*expanded;

	if (next_line(&line, sh))
		return (1);
	while (line)
	{
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
		{
			free(line);
			return (0);
		}
		expanded = expand_line(line, redir, sh);
		free(line);
		if (!expanded || write(pfd[1], expanded, ft_strlen(expanded)) < 0
			|| write(pfd[1], "\n", 1) < 0)
		{
			free(expanded);
			return (1);
		}
		free(expanded);
		if (next_line(&line, sh))
			return (1);
	}
	return (0);
}

static int	heredoc_fd(t_redir *redir, t_shell *sh)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		return (-1);
	if (fill_heredoc(pfd, redir, sh))
	{
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	close(pfd[1]);
	return (pfd[0]);
}

int	prepare_heredocs(t_command *cmd, t_shell *sh)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->heredoc_fd = heredoc_fd(redir, sh);
				if (redir->heredoc_fd < 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
