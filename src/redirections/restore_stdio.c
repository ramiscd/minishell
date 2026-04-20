/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stdio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:05:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 18:05:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		if (dup2(saved_stdin, STDIN_FILENO) < 0)
			perror("dup2");
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
			perror("dup2");
		close(saved_stdout);
	}
}
