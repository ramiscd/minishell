/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:47:07 by rdamasce          #+#    #+#             */
/*   Updated: 2026/03/05 20:32:55 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../headers/structs.h"
#include <stdlib.h>
#include <stdio.h>

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

int main()
{
	t_token *t = token_create("ls", WORD);
	printf("%s\n", t->cmd);
	printf("%d\n", t->type);
}