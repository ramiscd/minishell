/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 21:02:55 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:27:08 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin_dispatch(t_shell *sh, t_command *cmd);

static int	builtin_match(char *name, char *builtin)
{
	size_t	len;

	if (!name || !builtin)
		return (0);
	len = ft_strlen(builtin);
	return (!ft_strncmp(name, builtin, len + 1));
}

int	is_builtin(t_command *cmd)
{
	char	*name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	name = cmd->argv[0];
	return (builtin_match(name, "echo")
		|| builtin_match(name, "cd")
		|| builtin_match(name, "pwd")
		|| builtin_match(name, "export")
		|| builtin_match(name, "unset")
		|| builtin_match(name, "env")
		|| builtin_match(name, "exit"));
}

int	run_builtin_parent(t_shell *sh, t_command *cmd)
{
	return (run_builtin_dispatch(sh, cmd));
}

int	run_builtin_child(t_shell *sh, t_command *cmd)
{
	return (run_builtin_dispatch(sh, cmd));
}

int	execbi(t_shell *sh, t_command *cmd)
{
	return (run_builtin_parent(sh, cmd));
}
