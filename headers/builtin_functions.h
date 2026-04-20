/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 23:14:12 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 14:20:28 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FUNCTIONS_H
# define BUILTIN_FUNCTIONS_H

/**
 * Libs inluded to build the Built-in functions
*/
# include <unistd.h>

typedef struct s_mini		t_mini;
typedef struct s_command	t_command;
typedef struct s_mini		t_shell;

void	ft_echo(t_shell *sh, t_command *cmd);
void	ft_cd(t_shell *sh, t_command *cmd);
void	ft_env(t_shell *sh, t_command *cmd);
void	ft_pwd(t_shell *sh, t_command *cmd);
void	ft_export(t_shell *sh, t_command *cmd);
void	ft_unset(t_shell *sh, t_command *cmd);
void	ft_exit(t_shell *sh, t_command *cmd);
int		is_builtin(t_command *cmd);
int		run_builtin_parent(t_shell *sh, t_command *cmd);
int		run_builtin_child(t_shell *sh, t_command *cmd);

#endif
