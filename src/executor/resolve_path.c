/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_dir(char *dir, char *cmd)
{
	char	*full;

	full = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, ft_strlen(dir) + 1);
	ft_strlcat(full, "/", ft_strlen(dir) + 2);
	ft_strlcat(full, cmd, ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_path(char *cmd, char *path_copy)
{
	char	*dir;
	char	*next;
	char	*full;

	dir = path_copy;
	while (dir)
	{
		next = ft_strchr(dir, ':');
		if (next)
			*next++ = '\0';
		full = try_dir(dir, cmd);
		if (full)
			return (free(path_copy), full);
		dir = next;
	}
	free(path_copy);
	return (NULL);
}

char	*resolve_path(t_shell *sh, char *cmd)
{
	char	*path_env;
	char	*path_copy;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = env_get(sh, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	return (search_path(cmd, path_copy));
}
