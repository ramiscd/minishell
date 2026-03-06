/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:47:16 by vade-mel          #+#    #+#             */
/*   Updated: 2026/03/05 22:13:16 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *ms, char **cmd)
{
	char	new_line;
	int		i;
	int		j;

	new_line = 1;
	i = 1;
	while (cmd && cmd[i] && !ft_strncmp (cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (cmd && cmd[i])
	{
		ft_printf ("%s", cmd[i]);
		if (cmd[++i])
			ft_putchar_fd (' ', 1);
	}
	if (new_line)
		ft_printf ("\n");
	ms -> error = 0;
}

