/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:02:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:19 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_command	t_command;
typedef struct s_redir		t_redir;

int		apply_redirs(t_command *cmd, int *saved_stdin, int *saved_stdout);
void	restore_stdio(int saved_stdin, int saved_stdout);

#endif
