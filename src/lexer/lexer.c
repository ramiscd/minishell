/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:14:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/03/31 20:43:03 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../headers/structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* input: "ls -la | grep txt"

tokens esperados:

[WORD: ls]
[WORD: -la]
[PIPE: |]
[WORD: grep]
[WORD: txt] */

// typedef enum e_token_type
// {
// 	WORD,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	HEREDOC,
// 	APPEND,
// } t_token_type;

t_token *lexer(char *input)
{
	t_token *head = NULL;
	t_token *new_token;
	int i = 0;

	while (input[i])
	{
		// Pular espaços repetidos
		while (input[i] == ' ')
			i++;

		if (input[i] == '\0') // Se chegamos no fim, saímos
			break;

		// Caracteres especiais
		if (input[i] == '|')
		{
			new_token = token_create("|", PIPE);
			i++;
		}
		else if (input[i] == '>')
		{
			new_token = token_create(">", REDIR_OUT);
			i++;
		}
		else if (input[i] == '<')
		{
			new_token = token_create("<", REDIR_IN);
			i++;
		}
		else // Palavra comum
		{
			char *cmd = extract_word(input, &i);
			new_token = token_create(cmd, WORD);
		}

		if (new_token) // Só adiciona se realmente foi criado
			add_token_back(&head, new_token);
	}

	return head;
}

char *extract_word(char *input, int *i)
{
	int start = *i;
	// Avança até espaço ou caractere especial
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
		   input[*i] != '<' && input[*i] != '>')
		(*i)++;

	int len = *i - start;
	if (len == 0) // Se não tem nada, retorna NULL
		return NULL;

	char *new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return NULL;

	strncpy(new_str, input + start, len);
	new_str[len] = '\0';
	return new_str;
}



void print_tokens(t_token *head)
{
	t_token *current = head;
	int index = 0;

	while (current)
	{
		printf("Token %d: cmd='%s', type=%d\n", index, current->cmd, current->type);
		current = current->next;
		index++;
	}
}

// Função para liberar memória da lista de tokens
void free_tokens(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->type == WORD && tmp->cmd) // liberando apenas strings alocadas dinamicamente
			free(tmp->cmd);
		free(tmp);
	}
}

/* int main()
{
	char *input = "ls -la | grep txt";

	t_token *tokens = lexer(input);

	printf("Lista de tokens gerada:\n");
	print_tokens(tokens);

	free_tokens(tokens);

	return 0;
} */


