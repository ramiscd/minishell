#include "../headers/structs.h"
#include "../headers/lexer.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>

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