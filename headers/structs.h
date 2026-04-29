/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:45:59 by rdamasce          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**envp;
	t_token	*token;
	char	error;
	char	exit;
}	t_mini;

typedef struct s_expand
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;
	int		quotes;
	int		ex_n;
	int		i;
}	t_expand;

typedef struct s_executor
{
	t_token	*temp;
	char	**cmd;
	int		**fd;
	int		status;
	pid_t	*pid;
	int		n_pros;
}	t_executor;

typedef struct s_cmd_builder
{
	t_token		*tokens;
	t_token		*current;
	int			argc;
	char		**argv;
	t_redir		*redirs;
}	t_cmd_builder;

typedef struct s_buf
{
	char	*data;
	int		len;
	int		size;
	int		q;
}	t_buf;

typedef struct s_child_data
{
	int	*pipe_fds;
	int	i;
	int	n;
	int	last_status;
}	t_child_data;

#endif
