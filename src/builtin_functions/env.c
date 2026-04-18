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

void	ft_env(t_shell *sh, t_command *cmd)
{
	int	i;

	(void)cmd;
	if (!sh || !sh->envp)
	{
		if (sh)
			sh->error = 0;
		return ;
	}
	i = 0;
	while (sh->envp[i])
	{
		ft_printf("%s\n", sh->envp[i]);
		i++;
	}
	sh->error = 0;
}
