/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:41 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	init_shell(t_shell *sh, char **envp)
{
	sh->input = NULL;
	sh->prompt = "minishell$ ";
	sh->envp = envp;
	sh->token = NULL;
	sh->error = 0;
	sh->exit = 0;
}

static void	run_commands(t_shell *sh, t_command *cmds)
{
	t_command	*cmd;

	cmd = cmds;
	while (cmd && !sh->exit)
	{
		execute_command(sh, cmd);
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		sh;
	t_token		*tokens;
	t_command	*cmds;

	(void)ac;
	(void)av;
	init_shell(&sh, envp);
	while (!sh.exit)
	{
		sh.input = readline(sh.prompt);
		if (!sh.input)
			break ;
		if (*sh.input == '\0')
		{
			free(sh.input);
			continue ;
		}
		add_history(sh.input);
		tokens = lexer(sh.input);
		if (!tokens)
		{
			free(sh.input);
			continue ;
		}
		cmds = parse(tokens);
		free_tokens(tokens);
		if (cmds)
		{
			run_commands(&sh, cmds);
			free_command(cmds);
		}
		free(sh.input);
	}
	return (sh.error);
}
