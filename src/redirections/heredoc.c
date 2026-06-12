/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/06/12 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static char	*hd_readline(void)
{
	char	buf[4097];
	int		len;
	char	c;
	int		n;

	len = 0;
	n = 0;
	while (len < 4096)
	{
		n = read(STDIN_FILENO, &c, 1);
		if (n <= 0 || c == '\n')
			break ;
		buf[len++] = c;
	}
	if (len == 0 && n <= 0)
		return (NULL);
	buf[len] = '\0';
	return (ft_strdup(buf));
}

static char	*expand_line(char *line, t_redir *redir, t_shell *sh)
{
	if (redir->quoted)
		return (ft_strdup(line));
	return (expand_heredoc_line(line, sh));
}

static int	fill_heredoc(int *pfd, t_redir *redir, t_shell *sh)
{
	char	*line;
	char	*expanded;

	line = hd_readline();
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
		line = hd_readline();
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
