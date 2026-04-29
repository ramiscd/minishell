/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:45:41 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:26:55 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_command		*parse(t_token *tokens);
void			print_commands(t_command *cmd);

/* builder */
t_cmd_builder	*init_builder(t_token *tokens);
void			add_arg(t_cmd_builder *b, char *arg);

/* redirecionamentos */
t_redir			*create_redir(t_token *op, t_token *file);
void			add_redir(t_command *cmd, t_redir *redir);

/* build command */
t_command		*build_command(t_cmd_builder *b);

void			free_builder(t_cmd_builder *b);

void			free_redirs(t_redir *r);

void			free_command(t_command *cmd);

#endif
