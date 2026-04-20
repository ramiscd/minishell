/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:14:31 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"
#include <stdio.h>
#include <ctype.h>

static char	*expand_var(t_shell *sh, const char *name, int len)
{
	char	buf[16];
	char	key[256];
	char	*val;

	if (len == 1 && name[0] == '?')
	{
		snprintf(buf, sizeof(buf), "%d", (int)(unsigned char)sh->error);
		return (strdup(buf));
	}
	if (len <= 0 || len >= (int)sizeof(key))
		return (strdup("$"));
	memcpy(key, name, len);
	key[len] = '\0';
	val = env_get(sh, key);
	return (strdup(val ? val : ""));
}

static int	buf_grow(char **dst, int *dlen, int *dsize, const char *src,
		int slen)
{
	char	*tmp;

	while (*dlen + slen + 1 > *dsize)
	{
		tmp = malloc(*dsize * 2);
		if (!tmp)
			return (1);
		memcpy(tmp, *dst, *dlen);
		free(*dst);
		*dst = tmp;
		*dsize *= 2;
	}
	memcpy(*dst + *dlen, src, slen);
	*dlen += slen;
	(*dst)[*dlen] = '\0';
	return (0);
}

static int	expand_dollar(char *input, int *i, t_shell *sh,
		char **dst, int *dlen, int *dsize)
{
	char	name[256];
	int		nlen;
	char	*expanded;
	int		ret;

	(*i)++;
	nlen = 0;
	if (input[*i] == '?')
	{
		name[nlen++] = '?';
		(*i)++;
	}
	else
	{
		while (input[*i] && (isalnum((unsigned char)input[*i])
				|| input[*i] == '_'))
			name[nlen++] = input[(*i)++];
	}
	if (nlen == 0)
		return (buf_grow(dst, dlen, dsize, "$", 1));
	name[nlen] = '\0';
	expanded = expand_var(sh, name, nlen);
	if (!expanded)
		return (1);
	ret = buf_grow(dst, dlen, dsize, expanded, strlen(expanded));
	free(expanded);
	return (ret);
}

char	*extract_word(char *input, int *i, t_shell *sh)
{
	int		dsize;
	int		dlen;
	char	*dst;
	int		q;

	dsize = 64;
	dlen = 0;
	q = 0;
	dst = malloc(dsize);
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	while (input[*i])
	{
		if (q == 1 && input[*i] == '\'')
		{
			q = 0;
			(*i)++;
			continue ;
		}
		if (q == 2 && input[*i] == '"')
		{
			q = 0;
			(*i)++;
			continue ;
		}
		if (q == 0 && input[*i] == '\'')
		{
			q = 1;
			(*i)++;
			continue ;
		}
		if (q == 0 && input[*i] == '"')
		{
			q = 2;
			(*i)++;
			continue ;
		}
		if (q == 0 && (input[*i] == ' ' || input[*i] == '\t'
				|| input[*i] == '|' || input[*i] == '<'
				|| input[*i] == '>'))
			break ;
		if (q != 1 && input[*i] == '$' && input[*i + 1])
		{
			if (expand_dollar(input, i, sh, &dst, &dlen, &dsize))
			{
				free(dst);
				return (NULL);
			}
			continue ;
		}
		if (buf_grow(&dst, &dlen, &dsize, &input[*i], 1))
		{
			free(dst);
			return (NULL);
		}
		(*i)++;
	}
	if (dlen == 0)
	{
		free(dst);
		return (NULL);
	}
	return (dst);
}

static t_token	*handle_special(char *input, int *i)
{
	if (input[*i] == '|')
	{
		(*i)++;
		return (token_create("|", PIPE));
	}
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
	if (input[*i] == '<')
	{
		(*i)++;
		return (token_create("<", TOKEN_REDIR_IN));
	}
	return (NULL);
}

t_token	*lexer(char *input, t_shell *sh)
{
	t_token	*head;
	t_token	*new_token;
	char	*cmd;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '"'
			|| (input[i] != '|' && input[i] != '<' && input[i] != '>'))
		{
			cmd = extract_word(input, &i, sh);
			if (!cmd)
				return (free_tokens(head), NULL);
			new_token = token_create(cmd, WORD);
			free(cmd);
		}
		else
			new_token = handle_special(input, &i);
		if (!new_token)
			return (free_tokens(head), NULL);
		add_token_back(&head, new_token);
	}
	return (head);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
}
