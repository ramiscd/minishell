/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:30:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/03/28 12:30:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_invalid_args(t_mini *ms, char **cmd)
{
	if (!cmd || !cmd[1] || cmd[2])
	{
		ft_putendl_fd("cd: usage: cd <path>", 2);
		ms->error = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_mini *ms, char **cmd)
{
	if (!ms)
		return ;
	if (cd_invalid_args(ms, cmd))
		return ;
	if (chdir(cmd[1]) != 0)
	{
		perror("cd");
		ms->error = 1;
		return ;
	}
	ms->error = 0;
}
