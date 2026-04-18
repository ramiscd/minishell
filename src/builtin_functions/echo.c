/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:47:16 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 14:25:29 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	j;

	if (!arg || ft_strncmp(arg, "-n", 2))
		return (0);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	get_echo_start(char **argv)
{
	int	i;

	i = 1;
	while (argv && argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		if (!is_n_flag(argv[i]))
			break ;
		i++;
	}
	return (i);
}

static void	print_echo_args(char **argv, int i)
{
	while (argv && argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[++i])
			ft_putchar_fd(' ', 1);
	}
}

void	ft_echo(t_shell *sh, t_command *cmd)
{
	char	**argv;
	int		i;

	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	i = get_echo_start(argv);
	print_echo_args(argv, i);
	if (!argv || !argv[1] || !is_n_flag(argv[1]))
		ft_printf("\n");
	if (sh)
		sh->error = 0;
}
