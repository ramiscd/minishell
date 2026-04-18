/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 21:02:55 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/06 21:04:41 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execbi(t_mini *ms, char **cmd, char ***envp)
{
	if (!cmd || !*cmd || !*envp)
		return (-1);
	if (!ft_strncmp (*cmd, "echo", 5))
		ft_echo (ms, cmd);
	else if (!ft_strncmp (*cmd, "cd", 3))
		ft_cd (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "pwd", 4))
		ft_pwd (ms, cmd, *envp);
	else if (!ft_strncmp (*cmd, "export", 7))
		ft_export (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "unset", 6))
		ft_unset (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "env", 4))
		ft_env (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "exit", 5))
		ft_exit (ms, cmd);
	else
		return (0);
	return (1);
}
