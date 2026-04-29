/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:55:38 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*build_command(t_cmd_builder *b);

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		free_redirs(tmp->redirs);
		free(tmp);
	}
}

static void	add_to_list(t_command *cmd, t_command **head, t_command **last)
{
	if (!cmd)
		return ;
	if (!*head)
		*head = cmd;
	else
		(*last)->next = cmd;
	*last = cmd;
}

static int	handle_redirection(t_cmd_builder *b)
{
	t_redir	*r;
	t_redir	*tmp;

	if (!b->current->next || b->current->next->type != WORD)
		return (printf("Syntax error near redirection\n"), 0);
	r = create_redir(b->current, b->current->next);
	if (!b->redirs)
		b->redirs = r;
	else
	{
		tmp = b->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = r;
	}
	b->current = b->current->next->next;
	return (1);
}

static int	parse_step(t_cmd_builder *b, t_command **head, t_command **last)
{
	t_command	*cmd;

	if (b->current->type == WORD)
	{
		add_arg(b, strdup(b->current->cmd));
		b->current = b->current->next;
		return (1);
	}
	if (b->current->type >= TOKEN_REDIR_IN
		&& b->current->type <= TOKEN_APPEND)
		return (handle_redirection(b));
	if (b->current->type == PIPE)
	{
		if (b->argc == 0 && b->redirs == NULL)
			return (printf("Syntax error near pipe\n"), 0);
		cmd = build_command(b);
		add_to_list(cmd, head, last);
		b->current = b->current->next;
		return (1);
	}
	b->current = b->current->next;
	return (1);
}

t_command	*parse(t_token *tokens)
{
	t_cmd_builder	*b;
	t_command		*head;
	t_command		*last;
	t_command		*cmd;

	b = init_builder(tokens);
	head = NULL;
	last = NULL;
	if (tokens && tokens->type == PIPE)
		return (printf("Syntax error near pipe\n"), NULL);
	while (b && b->current)
	{
		if (!parse_step(b, &head, &last))
			return (free_builder(b), free_command(head), NULL);
	}
	if (b->argc > 0 || b->redirs)
	{
		cmd = build_command(b);
		add_to_list(cmd, &head, &last);
	}
	free_builder(b);
	return (head);
}
