/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:05:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 17:05:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_key_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

static int	export_valid_key(char *arg)
{
	int	i;
	int	len;

	len = export_key_len(arg);
	if (!len || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_apply(t_shell *sh, char *arg)
{
	int		len;
	char	*key;

	len = export_key_len(arg);
	if (!arg[len])
		return (0);
	if (!export_valid_key(arg))
		return (1);
	key = ft_substr(arg, 0, len);
	if (!key)
		return (1);
	if (env_set(sh, key, arg + len + 1))
	{
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

void	ft_export(t_shell *sh, t_command *cmd)
{
	char	**argv;
	int		i;
	int		err;

	argv = NULL;
	if (!sh)
		return ;
	if (cmd)
		argv = cmd->argv;
	i = 1;
	err = 0;
	while (argv && argv[i])
	{
		if (export_apply(sh, argv[i]))
			err = 1;
		i++;
	}
	sh->error = err;
}
