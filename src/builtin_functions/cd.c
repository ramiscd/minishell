/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:12 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_change_dir(char *path, char **oldpwd, char **newpwd);
int	cd_update_env(t_shell *sh, char *oldpwd, char *newpwd);

void	ft_cd(t_shell *sh, t_command *cmd)
{
	char	**argv;
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = NULL;
	newpwd = NULL;
	if (!sh)
		return ;
	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	if (argv && argv[1] && argv[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		sh->error = 1;
		return ;
	}
	if (!argv || !argv[1])
		path = env_get(sh, "HOME");
	else
		path = argv[1];
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		sh->error = 1;
		return ;
	}
	if (cd_change_dir(path, &oldpwd, &newpwd))
	{
		sh->error = 1;
		return ;
	}
	sh->error = cd_update_env(sh, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
}
