/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:45:37 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:21 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

typedef struct s_mini	t_shell;

t_token	*lexer(char *input, t_shell *sh);
t_token	*token_create(char *cmd, int type);
void	add_token_back(t_token **head, t_token *new);
char	*extract_word(char *input, int *i, t_shell *sh);
void	free_tokens(t_token *head);
int		buf_grow(t_buf *buf, const char *src, int slen);
int		expand_dollar(char *input, int *i, t_shell *sh, t_buf *buf);

#endif
