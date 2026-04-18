/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:31:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:31:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_find_key_index(char **envp, const char *key);

int	env_unset(t_shell *sh, const char *key)
{
	int	index;

	if (!sh || !sh->envp || !key || !*key)
		return (1);
	index = env_find_key_index(sh->envp, key);
	if (index < 0)
		return (0);
	free(sh->envp[index]);
	while (sh->envp[index])
	{
		sh->envp[index] = sh->envp[index + 1];
		index++;
	}
	return (0);
}
