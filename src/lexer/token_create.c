/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:47:07 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 20:17:04 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Creates a new token for the shell.
 *
 *
 * @code
 * // Example usage:
 * t_token *t = token_create("ls", WORD);
 * printf("%s %d\n", t->cmd, t->type);
 *
 * // Expected output:
 * ls 0   // assuming WORD = 0 in t_token_type enum
 * @endcode
 */
t_token	*token_create(char *cmd, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = strdup(cmd);
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}
