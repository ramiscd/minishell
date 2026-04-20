/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:30:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_key_len(const char *key)
{
	size_t	i;

	i = 0;
	while (key && key[i] && key[i] != '=')
		i++;
	return (i);
}

static int	env_key_match(char *entry, const char *key)
{
	size_t	i;

	i = 0;
	if (!entry || !key)
		return (0);
	while (key[i] && key[i] != '=' && entry[i] == key[i])
		i++;
	return (key[i] == '\0' && entry[i] == '=');
}

int	env_find_key_index(char **envp, const char *key)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (env_key_match(envp[i], key))
			return (i);
		i++;
	}
	return (-1);
}

char	*env_build_entry(const char *key, const char *value)
{
	char	*entry;
	size_t	key_size;
	size_t	value_size;
	size_t	i;

	key_size = env_key_len(key);
	value_size = ft_strlen(value);
	entry = malloc(sizeof(char) * (key_size + value_size + 2));
	if (!entry)
		return (NULL);
	i = 0;
	while (i < key_size)
	{
		entry[i] = key[i];
		i++;
	}
	entry[i++] = '=';
	while (*value)
		entry[i++] = *value++;
	entry[i] = '\0';
	return (entry);
}
