/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:07:23 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 20:16:45 by rdamasce         ###   ########.fr       */
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
