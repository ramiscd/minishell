/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:41 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/07 21:34:11 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int	main(int ac, char **av)
{
	t_token		*tokens;
	t_command	*cmds;

	if (ac != 2)
	{
		printf("Usage: ./minishell \"command\"\n");
		return (1);
	}
	tokens = lexer(av[1]);
	if (!tokens)
	{
		printf("Lexer failed\n");
		return (1);
	}
	cmds = parse(tokens);
	if (!cmds)
	{
		printf("Parse failed\n");
		return (1);
	}
	print_commands(cmds);
	return (0);
}
