/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:10:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/18 15:10:00 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_mini	t_shell;

char	*env_get(t_shell *sh, const char *key);
int		env_set(t_shell *sh, const char *key, const char *value);
int		env_unset(t_shell *sh, const char *key);
char	**copy_envp(char **envp);
void	free_envp(char **envp);

#endif
