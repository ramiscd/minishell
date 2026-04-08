/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:31:39 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*create_redir(t_token *op, t_token *file)
{
	t_redir *r = malloc(sizeof(t_redir));

	if (!r)
		return (NULL);
	r->file = strdup(file->cmd);
	if (op->type == TOKEN_REDIR_IN)
		r->type = REDIR_IN;
	else if (op->type == TOKEN_REDIR_OUT)
		r->type = REDIR_OUT;
	else if (op->type == TOKEN_HEREDOC)
		r->type = HEREDOC;
	else if (op->type == TOKEN_APPEND)
		r->type = APPEND;
	r->next = NULL;
	return (r);
}

void	add_redir(t_command *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}
