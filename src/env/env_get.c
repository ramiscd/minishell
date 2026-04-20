/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:30:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_find_key_index(char **envp, const char *key);

char	*env_get(t_shell *sh, const char *key)
{
	int		index;
	size_t	i;

	if (!sh || !sh->envp || !key || !*key)
		return (NULL);
	index = env_find_key_index(sh->envp, key);
	if (index < 0)
		return (NULL);
	i = 0;
	while (sh->envp[index][i] && sh->envp[index][i] != '=')
		i++;
	if (sh->envp[index][i] == '=')
		return (&sh->envp[index][i + 1]);
	return (NULL);
}
