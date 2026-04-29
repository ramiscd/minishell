/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_change_dir(char *path, char **oldpwd, char **newpwd);
int	cd_update_env(t_shell *sh, char *oldpwd, char *newpwd);

static char	*cd_get_path(t_shell *sh, char **argv)
{
	if (argv && argv[1] && argv[2])
		return (NULL);
	if (!argv || !argv[1])
		return (env_get(sh, "HOME"));
	return (argv[1]);
}

static int	cd_validate(t_shell *sh, char **argv, char **path_out)
{
	if (argv && argv[1] && argv[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		sh->error = 1;
		return (1);
	}
	*path_out = cd_get_path(sh, argv);
	if (!*path_out)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		sh->error = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *sh, t_command *cmd)
{
	char	**argv;
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (!sh)
		return ;
	argv = NULL;
	if (cmd)
		argv = cmd->argv;
	if (cd_validate(sh, argv, &path))
		return ;
	oldpwd = NULL;
	newpwd = NULL;
	if (cd_change_dir(path, &oldpwd, &newpwd))
	{
		sh->error = 1;
		return ;
	}
	sh->error = cd_update_env(sh, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
}
