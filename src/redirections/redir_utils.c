/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:04:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 18:04:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	redir_target_fd(int type)
{
	if (type == REDIR_IN)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	redir_open_fd(t_redir *redir)
{
	if (!redir || !redir->file)
		return (-1);
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644));
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
