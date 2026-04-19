/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:02:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 18:02:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_command	t_command;
typedef struct s_redir		t_redir;

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3

int		apply_redirs(t_command *cmd, int *saved_stdin, int *saved_stdout);
void	restore_stdio(int saved_stdin, int saved_stdout);

#endif
