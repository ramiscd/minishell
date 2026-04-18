/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 16:30:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_rollback_env(t_shell *sh, char *old_bkp, char *pwd_bkp)
{
	int	err;

	err = 0;
	if (old_bkp && env_set(sh, "OLDPWD", old_bkp))
		err = 1;
	if (!old_bkp && env_unset(sh, "OLDPWD"))
		err = 1;
	if (pwd_bkp && env_set(sh, "PWD", pwd_bkp))
		err = 1;
	if (!pwd_bkp && env_unset(sh, "PWD"))
		err = 1;
	return (err);
}

static int	cd_backup_env(t_shell *sh, char **old_bkp, char **pwd_bkp)
{
	char	*old_ref;
	char	*pwd_ref;

	old_ref = env_get(sh, "OLDPWD");
	pwd_ref = env_get(sh, "PWD");
	*old_bkp = NULL;
	*pwd_bkp = NULL;
	if (old_ref)
		*old_bkp = ft_strdup(old_ref);
	if (pwd_ref)
		*pwd_bkp = ft_strdup(pwd_ref);
	if ((old_ref && !*old_bkp) || (pwd_ref && !*pwd_bkp))
	{
		free(*old_bkp);
		free(*pwd_bkp);
		return (1);
	}
	return (0);
}

int	cd_update_env(t_shell *sh, char *oldpwd, char *newpwd)
{
	char	*old_bkp;
	char	*pwd_bkp;

	if (cd_backup_env(sh, &old_bkp, &pwd_bkp))
		return (1);
	if (env_set(sh, "OLDPWD", oldpwd) || env_set(sh, "PWD", newpwd))
	{
		cd_rollback_env(sh, old_bkp, pwd_bkp);
		free(old_bkp);
		free(pwd_bkp);
		return (1);
	}
	free(old_bkp);
	free(pwd_bkp);
	return (0);
}

int	cd_change_dir(char *path, char **oldpwd, char **newpwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(*oldpwd);
		*oldpwd = NULL;
		return (1);
	}
	*newpwd = getcwd(NULL, 0);
	if (!*oldpwd || !*newpwd)
	{
		free(*oldpwd);
		free(*newpwd);
		*oldpwd = NULL;
		*newpwd = NULL;
		return (1);
	}
	return (0);
}
