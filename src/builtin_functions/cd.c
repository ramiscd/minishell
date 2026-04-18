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

int	cd_change_dir(char *path, char **oldpwd, char **newpwd);
int	cd_update_env(t_shell *sh, char *oldpwd, char *newpwd);

static int	cd_validate_args(t_shell *sh, char **argv)
{
	if (!argv || !argv[1] || argv[2])
	{
		ft_putendl_fd("cd: usage: cd <path>", 2);
		sh->error = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *sh, t_command *cmd)
{
	char	**argv;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = NULL;
	newpwd = NULL;
	if (!sh)
		return ;
	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	if (cd_validate_args(sh, argv))
		return ;
	if (cd_change_dir(argv[1], &oldpwd, &newpwd))
	{
		sh->error = 1;
		return ;
	}
	sh->error = cd_update_env(sh, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
}
