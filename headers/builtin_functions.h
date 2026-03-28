/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 23:14:12 by vade-mel          #+#    #+#             */
/*   Updated: 2026/03/05 22:11:08 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_FUNCTIONS_H
# define  BUILTIN_FUNCTIONS_H

/**
 * Libs inluded to build the Built-in functions
*/
# include <unistd.h>

typedef struct s_mini	t_mini;

void	ft_echo(t_mini *ms, char **cmd);
void	ft_pwd(t_mini *ms, char **cmd);

#endif
