/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:05:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/03/28 12:05:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *ms, char **cmd)
{
	int	i;

	(void)cmd;
	if (!ms || !ms->envp)
	{
		if (ms)
			ms->error = 0;
		return ;
	}
	i = 0;
	while (ms->envp[i])
	{
		ft_printf("%s\n", ms->envp[i]);
		i++;
	}
	ms->error = 0;
}
