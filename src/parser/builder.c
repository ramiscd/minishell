/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:27 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 20:33:18 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	copy_argv(char **new_argv, char **old_argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
}

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

	if (!b)
		return ;
	if (!b->argv)
		new_argv = malloc(sizeof(char *) * 2);
	else
	{
		new_argv = malloc(sizeof(char *) * (b->argc + 2));
		if (new_argv)
		{
			copy_argv(new_argv, b->argv, b->argc);
			free(b->argv);
		}
	}
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

void	free_builder(t_cmd_builder *b)
{
	if (!b)
		return ;
	if (b->argv)
		free(b->argv);
	free(b);
}
