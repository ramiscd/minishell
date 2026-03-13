/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:47:07 by rdamasce          #+#    #+#             */
/*   Updated: 2026/03/10 20:15:20 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../headers/structs.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Creates a new token for the shell.
 *
 * Allocates memory for a t_token struct, initializes its fields with
 * the given command string and token type, and sets the next and prev
 * pointers to NULL.
 *
 * @param cmd The command string or value of the token.
 * @param type The type of the token, defined by the t_token_type enum (e.g., WORD, PIPE, REDIR_IN).
 * @return A pointer to the newly created t_token struct, or NULL if memory allocation fails.
 *
 * @note The caller is responsible for freeing the memory allocated for
 * both the token and the cmd string if dynamically allocated.
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
t_token *token_create(char *cmd, int type)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->cmd = cmd;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;

	return (token);
}

/* int main()
{
	t_token *t = token_create("ls", WORD);
	printf("%s\n", t->cmd);
	printf("%d\n", t->type);

	free(t->cmd);
	free(t);
} */