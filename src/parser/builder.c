/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:27 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:43:14 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_builder	*init_builder(t_token *tokens)
{
	t_cmd_builder	*b;

	b = malloc(sizeof(t_cmd_builder));
	if (!b)
		return (NULL);
	b->tokens = tokens;
	b->current = tokens;
	b->argc = 0;
	b->argv = NULL;
	b->redirs = NULL;
	return (b);
}

void	add_arg(t_cmd_builder *b, char *arg)
{
	char	**new_argv;

	if (!b->argv)
		new_argv = malloc(sizeof(char *) * 2);
	else
		new_argv = realloc(b->argv, sizeof(char *) * (b->argc + 2));
	if (!new_argv)
		return ;
	b->argv = new_argv;
	b->argv[b->argc] = arg;
	b->argc++;
	b->argv[b->argc] = NULL;
}

t_command	*build_command(t_cmd_builder *b)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = b->argv;
	cmd->redirs = b->redirs;
	cmd->next = NULL;
	b->argc = 0;
	b->argv = NULL;
	b->redirs = NULL;
	return (cmd);
}
