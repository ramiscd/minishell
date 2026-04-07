/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:27 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 20:15:58 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_builder *init_builder(t_token *tokens)
{
    t_cmd_builder *b = malloc(sizeof(t_cmd_builder));
    if (!b) return NULL;

    b->tokens = tokens;
    b->current = tokens;
    b->argc = 0;
    b->argv = NULL;
    b->redirs = NULL;   // 🔥 FALTAVA ISSO

    return b;
}

void add_arg(t_cmd_builder *b, char *arg)
{
    if (!b->argv)
        b->argv = malloc(sizeof(char *) * 2);
    else
        b->argv = realloc(b->argv, sizeof(char *) * (b->argc + 2));

    b->argv[b->argc] = arg;
    b->argc++;
    b->argv[b->argc] = NULL;
}

t_command *build_command(t_cmd_builder *b)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    cmd->argv = b->argv;
    cmd->redirs = b->redirs;
    cmd->next = NULL;

    // reset builder
    b->argc = 0;
    b->argv = NULL;
    b->redirs = NULL;

    return cmd;
}