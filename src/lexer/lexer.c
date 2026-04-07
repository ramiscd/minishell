/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:14:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 20:15:23 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *lexer(char *input)
{
	t_token *head = NULL;
	t_token *new_token;
	int i = 0;

	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break;
		if (input[i] == '|')
		{
			new_token = token_create("|", PIPE);
			i++;
		}
		else if (input[i] == '>')
		{
			new_token = token_create(">", TOKEN_REDIR_OUT);
			i++;
		}
		else if (input[i] == '<')
		{
			new_token = token_create("<", TOKEN_REDIR_IN);
			i++;
		}
		else
		{
			char *cmd = extract_word(input, &i);
			new_token = token_create(cmd, WORD);
		}

		if (new_token)
			add_token_back(&head, new_token);
	}

	return head;
}

char *extract_word(char *input, int *i)
{
	int start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
		   input[*i] != '<' && input[*i] != '>')
		(*i)++;

	int len = *i - start;
	if (len == 0)
		return NULL;

	char *new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return NULL;

	strncpy(new_str, input + start, len);
	new_str[len] = '\0';
	return new_str;
}

void free_tokens(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->type == WORD && tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
}

// Função temporaria
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

/* int main()
{
	char *input = "ls -la | grep txt";

	t_token *tokens = lexer(input);

	printf("Lista de tokens gerada:\n");
	print_tokens(tokens);

	free_tokens(tokens);

	return 0;
} */


