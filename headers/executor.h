/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:20:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:23 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_mini		t_shell;
typedef struct s_command	t_command;

char	*resolve_path(t_shell *sh, char *cmd);
int		execute_command(t_shell *sh, t_command *cmd);
void	execute_pipeline(t_shell *sh, t_command *head);

#endif
