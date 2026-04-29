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

static int	handle_quotes(t_buf *buf, char *input, int *i)
{
	if (buf->q == 1 && input[*i] == '\'')
		return (buf->q = 0, (*i)++, 1);
	if (buf->q == 2 && input[*i] == '"')
		return (buf->q = 0, (*i)++, 1);
	if (buf->q == 0 && input[*i] == '\'')
		return (buf->q = 1, (*i)++, 1);
	if (buf->q == 0 && input[*i] == '"')
		return (buf->q = 2, (*i)++, 1);
	return (0);
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

char	*extract_word(char *input, int *i, t_shell *sh)
{
	t_buf	buf;
	int		ret;

	buf.size = 64;
	buf.len = 0;
	buf.q = 0;
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
	if (buf.len == 0)
		return (free(buf.data), NULL);
	return (buf.data);
}
