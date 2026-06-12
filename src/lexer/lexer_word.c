/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	close_quote(t_buf *buf, char c, int *i)
{
	if (buf->q == 1 && c == '\'')
		buf->q = 0;
	else if (buf->q == 2 && c == '"')
		buf->q = 0;
	else
		return (0);
	(*i)++;
	return (1);
}

static int	open_quote(t_buf *buf, char c, int *i)
{
	if (buf->q != 0)
		return (0);
	if (c == '\'')
		buf->q = 1;
	else if (c == '"')
		buf->q = 2;
	else
		return (0);
	buf->quoted = 1;
	(*i)++;
	return (1);
}

static int	handle_quotes(t_buf *buf, char *input, int *i)
{
	if (close_quote(buf, input[*i], i))
		return (1);
	return (open_quote(buf, input[*i], i));
}

static int	process_char(t_buf *buf, char *input, int *i, t_shell *sh)
{
	if (handle_quotes(buf, input, i))
		return (0);
	if (buf->q == 0 && (input[*i] == ' ' || input[*i] == '\t'
			|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>'))
		return (1);
	if (buf->q != 1 && input[*i] == '$' && input[*i + 1])
	{
		if (expand_dollar(input, i, sh, buf))
			return (-1);
		return (0);
	}
	if (buf_grow(buf, &input[*i], 1))
		return (-1);
	(*i)++;
	return (0);
}

char	*extract_word(char *input, int *i, t_shell *sh, int *quoted)
{
	t_buf	buf;
	int		ret;

	buf.size = 64;
	buf.len = 0;
	buf.q = 0;
	buf.quoted = 0;
	buf.data = malloc(buf.size);
	if (!buf.data)
		return (NULL);
	buf.data[0] = '\0';
	while (input[*i])
	{
		ret = process_char(&buf, input, i, sh);
		if (ret == 1)
			break ;
		if (ret == -1)
			return (free(buf.data), NULL);
	}
	if (quoted)
		*quoted = buf.quoted;
	if (buf.len == 0 && !buf.quoted)
		return (free(buf.data), NULL);
	return (buf.data);
}
