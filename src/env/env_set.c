/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:31:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:31:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_find_key_index(char **envp, const char *key);
char	*env_build_entry(const char *key, const char *value);

static int	update_existing_entry(t_shell *sh, char *entry, const char *key)
{
	int		index;

	index = env_find_key_index(sh->envp, key);
	if (index >= 0)
	{
		free(sh->envp[index]);
		sh->envp[index] = entry;
		return (1);
	}
	return (0);
}

static int	append_new_entry(t_shell *sh, char *entry)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while (sh->envp && sh->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < count)
	{
		new_envp[i] = sh->envp[i];
		i++;
	}
	new_envp[count] = entry;
	new_envp[count + 1] = NULL;
	free(sh->envp);
	sh->envp = new_envp;
	return (0);
}

int	env_set(t_shell *sh, const char *key, const char *value)
{
	char	*entry;

	if (!sh || !key || !*key || !value)
		return (1);
	entry = env_build_entry(key, value);
	if (!entry)
		return (1);
	if (update_existing_entry(sh, entry, key))
		return (0);
	if (append_new_entry(sh, entry))
	{
		free(entry);
		return (1);
	}
	return (0);
}
