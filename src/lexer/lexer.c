/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:14:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*handle_angle(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i) += 2;
		return (token_create(">>", TOKEN_APPEND));
	}
	if (input[*i] == '>')
	{
		(*i)++;
		return (token_create(">", TOKEN_REDIR_OUT));
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i) += 2;
		return (token_create("<<", TOKEN_HEREDOC));
	}
	(*i)++;
	return (token_create("<", TOKEN_REDIR_IN));
}

static t_token	*handle_special(char *input, int *i)
{
	if (input[*i] == '|')
	{
		(*i)++;
		return (token_create("|", PIPE));
	}
	return (handle_angle(input, i));
}

static t_token	*next_token(char *input, int *i, t_shell *sh)
{
	t_token	*tok;
	char	*cmd;

	if (input[*i] == '\'' || input[*i] == '"'
		|| (input[*i] != '|' && input[*i] != '<' && input[*i] != '>'))
	{
		cmd = extract_word(input, i, sh);
		if (!cmd)
			return (NULL);
		tok = token_create(cmd, WORD);
		free(cmd);
		return (tok);
	}
	return (handle_special(input, i));
}

t_token	*lexer(char *input, t_shell *sh)
{
	t_token	*head;
	t_token	*new_token;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		new_token = next_token(input, &i, sh);
		if (!new_token)
			return (free_tokens(head), NULL);
		add_token_back(&head, new_token);
	}
	return (head);
}
