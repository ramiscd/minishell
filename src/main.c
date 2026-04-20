/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:46:41 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:14 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static void	sigint_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	setup_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

static char	**copy_envp(char **envp)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (envp && envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = strdup(envp[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

static void	init_shell(t_shell *sh, char **envp)
{
	sh->input = NULL;
	sh->prompt = "minishell$ ";
	sh->envp = copy_envp(envp);
	sh->token = NULL;
	sh->error = 0;
	sh->exit = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_shell		sh;
	t_token		*tokens;
	t_command	*cmds;

	(void)ac;
	(void)av;
	init_shell(&sh, envp);
	rl_outstream = stderr;
	setup_signals();
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
		tokens = lexer(sh.input, &sh);
		if (!tokens)
		{
			free(sh.input);
			continue ;
		}
		cmds = parse(tokens);
		free_tokens(tokens);
		if (cmds)
		{
			execute_pipeline(&sh, cmds);
			free_command(cmds);
		}
		free(sh.input);
	}
	return ((unsigned char)sh.error);
}
