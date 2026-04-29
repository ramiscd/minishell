/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
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
	if (len <= 0 || len >= (int) sizeof(key))
		return (strdup("$"));
	memcpy(key, name, len);
	key[len] = '\0';
	val = env_get(sh, key);
	if (val)
		return (strdup(val));
	return (strdup(""));
}

int	buf_grow(t_buf *buf, const char *src, int slen)
{
	char	*tmp;

	while (buf->len + slen + 1 > buf->size)
	{
		tmp = malloc(buf->size * 2);
		if (!tmp)
			return (1);
		memcpy(tmp, buf->data, buf->len);
		free(buf->data);
		buf->data = tmp;
		buf->size *= 2;
	}
	memcpy(buf->data + buf->len, src, slen);
	buf->len += slen;
	buf->data[buf->len] = '\0';
	return (0);
}

static int	read_varname(char *input, int *i, char *name)
{
	int	nlen;

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
	return (nlen);
}

int	expand_dollar(char *input, int *i, t_shell *sh, t_buf *buf)
{
	char	name[256];
	int		nlen;
	char	*expanded;
	int		ret;

	(*i)++;
	nlen = read_varname(input, i, name);
	if (nlen == 0)
		return (buf_grow(buf, "$", 1));
	name[nlen] = '\0';
	expanded = expand_var(sh, name, nlen);
	if (!expanded)
		return (1);
	ret = buf_grow(buf, expanded, strlen(expanded));
	free(expanded);
	return (ret);
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
