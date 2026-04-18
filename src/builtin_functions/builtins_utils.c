/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:56:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 14:56:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_match(char *name, char *builtin)
{
	size_t	len;

	if (!name || !builtin)
		return (0);
	len = ft_strlen(builtin);
	return (!ft_strncmp(name, builtin, len + 1));
}

int	run_builtin_dispatch(t_shell *sh, t_command *cmd)
{
	char	*name;

	if (!sh || !is_builtin(cmd))
		return (0);
	name = cmd->argv[0];
	if (builtin_match(name, "echo"))
		ft_echo(sh, cmd);
	else if (builtin_match(name, "cd"))
		ft_cd(sh, cmd);
	else if (builtin_match(name, "pwd"))
		ft_pwd(sh, cmd);
	else if (builtin_match(name, "env"))
		ft_env(sh, cmd);
	else
		sh->error = 0;
	return (1);
}
