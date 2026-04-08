/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:07:23 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:29:22 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	new->next = NULL;
	current = *head;
	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}
// Testando funcao.
/* void main()
{
	t_token *head = NULL;

	t_token *token1 = malloc(sizeof(t_token));
	token1->cmd = "ls";
	token1->type = 1;
	token1->next = NULL;
	token1->prev = NULL;

	add_token_back(&head, token1);

	printf("Teste 1 - Lista com 1 elemento: \n");
	printf("Head cmd: %s\n", head->cmd); // deve imprimir "ls"
	printf("Head prev: %p\n", head->prev); // deve imprimir NULL
	printf("Head next: %p\n", head->next); // deve imprimir NULL

	t_token *token2 = malloc(sizeof(t_token));
	token2->cmd = "pwd";
	token2->type = 2;
	token2->next = NULL;
	token2->prev = NULL;

	add_token_back(&head, token2);

	printf("Teste 2 - Lista com 2 elementos:\n");
	printf("Head cmd: %s\n", head->cmd);
	printf("Segundo comando cmd: %s\n", head->next->cmd);
	printf("Segundo comando prev cmd: %s\n", head->next->prev->cmd);
	printf("Segundo next: %p\n", head->next->next);
} */
