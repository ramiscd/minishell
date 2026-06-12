/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/06/12 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*expand_heredoc_line(char *line, t_shell *sh)
{
	t_buf	buf;
	int		i;

	buf.size = 64;
	buf.len = 0;
	buf.q = 0;
	buf.quoted = 0;
	buf.data = malloc(buf.size);
	if (!buf.data)
		return (NULL);
	buf.data[0] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && expand_dollar(line, &i, sh, &buf))
			return (free(buf.data), NULL);
		else if (line[i] && buf_grow(&buf, &line[i++], 1))
			return (free(buf.data), NULL);
	}
	return (buf.data);
}
