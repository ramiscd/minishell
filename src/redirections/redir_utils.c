/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:04:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:51:57 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	redir_target_fd(t_redir_type type)
{
	if (type == REDIR_IN || type == HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

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

static int	heredoc_fd(const char *delim)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) < 0)
		return (-1);
	line = hd_readline();
	while (line)
	{
		if (ft_strncmp(line, (char *)delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
		line = hd_readline();
	}
	close(pfd[1]);
	return (pfd[0]);
}

static int	redir_open_fd(t_redir *redir)
{
	if (!redir || !redir->file)
		return (-1);
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644));
	if (redir->type == HEREDOC)
		return (heredoc_fd(redir->file));
	return (-1);
}

int	redir_apply_node(t_redir *redir)
{
	int	fd;
	int	target;

	fd = redir_open_fd(redir);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	target = redir_target_fd(redir->type);
	if (dup2(fd, target) < 0)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}
