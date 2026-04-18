/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/03/28 12:30:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_invalid_args(t_shell *sh, t_command *cmd)
{
	char	**argv;

	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	if (!argv || !argv[1] || argv[2])
	{
		ft_putendl_fd("cd: usage: cd <path>", 2);
		if (sh)
			sh->error = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *sh, t_command *cmd)
{
	char	**argv;

	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	if (!sh)
		return ;
	if (cd_invalid_args(sh, cmd))
		return ;
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		sh->error = 1;
		return ;
	}
	sh->error = 0;
}
