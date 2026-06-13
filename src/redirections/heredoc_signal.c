/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/06/13 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

static volatile sig_atomic_t	*hd_sigint_flag(void)
{
	static volatile sig_atomic_t	flag;

	return (&flag);
}

static void	shell_sigint_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	*hd_sigint_flag() = 1;
	write(STDERR_FILENO, "\n", 1);
	rl_done = 1;
}

char	*heredoc_readline(void)
{
	char	*line;

	*hd_sigint_flag() = 0;
	signal(SIGINT, heredoc_sigint_handler);
	line = readline("> ");
	signal(SIGINT, shell_sigint_handler);
	if (*hd_sigint_flag())
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	heredoc_interrupted(t_shell *sh)
{
	if (!*hd_sigint_flag())
		return (0);
	sh->error = (char)130;
	return (1);
}
