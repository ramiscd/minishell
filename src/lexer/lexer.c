/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:14:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:49:16 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*handle_special(char c, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (c == '|')
	{
		new_token = token_create("|", PIPE);
		(*i)++;
	}
	else if (c == '>')
	{
		new_token = token_create(">", TOKEN_REDIR_OUT);
		(*i)++;
	}
	else if (c == '<')
	{
		new_token = token_create("<", TOKEN_REDIR_IN);
		(*i)++;
	}
	return (new_token);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*new_token;
	char	*cmd;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		new_token = handle_special(input[i], &i);
		if (!new_token)
		{
			cmd = extract_word(input, &i);
			new_token = token_create(cmd, WORD);
		}
		if (new_token)
			add_token_back(&head, new_token);
	}
	return (head);
}

char	*extract_word(char *input, int *i)
{
	int		start;
	int		len;
	char	*new_str;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '|'
		&& input[*i] != '<'
		&& input[*i] != '>')
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	strncpy(new_str, input + start, len);
	new_str[len] = '\0';
	return (new_str);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->type == WORD && tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;
	int		index;

	current = head;
	index = 0;
	while (current)
	{
		printf("Token %d: cmd='%s', type=%d\n",
			index, current->cmd, current->type);
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
