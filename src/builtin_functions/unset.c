/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:06:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 17:06:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *sh, t_command *cmd)
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
		if (env_unset(sh, argv[i]))
			err = 1;
		i++;
	}
	sh->error = err;
}
