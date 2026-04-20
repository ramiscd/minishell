/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:06:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 17:06:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *sh, t_command *cmd)
{
	char	**argv;

	argv = NULL;
	if (!sh)
		return ;
	if (cmd)
		argv = cmd->argv;
	if (argv && argv[1] && argv[2])
	{
		sh->error = 1;
		return ;
	}
	sh->exit = 1;
	sh->error = 0;
}
