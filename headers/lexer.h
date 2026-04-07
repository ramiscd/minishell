/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:45:37 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 19:45:38 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

t_token	*lexer(char *input);
t_token	*token_create(char *cmd, int type);
void	add_token_back(t_token **head, t_token *new);
char	*extract_word(char *input, int *i);

#endif