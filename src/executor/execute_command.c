/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:20:00 by vade-mel          #+#    #+#             */
/*   Updated: 2026/04/20 19:52:07 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

char	*resolve_path(t_shell *sh, char *cmd)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*next;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = env_get(sh, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = path_copy;
	while (dir)
	{
		next = ft_strchr(dir, ':');
		if (next)
			*next++ = '\0';
		full = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
		if (full)
		{
			ft_strlcpy(full, dir, ft_strlen(dir) + 1);
			ft_strlcat(full, "/", ft_strlen(dir) + 2);
			ft_strlcat(full, cmd, ft_strlen(dir) + ft_strlen(cmd) + 2);
			if (access(full, X_OK) == 0)
			{
				free(path_copy);
				return (full);
			}
			free(full);
		}
		dir = next;
	}
	free(path_copy);
	return (NULL);
}

static int	store_status(t_shell *sh, int status)
{
	if (WIFEXITED(status))
		sh->error = (char)WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->error = (char)(128 + WTERMSIG(status));
	else
		sh->error = 1;
	return (sh->error != 0);
}

static int	wait_and_restore(pid_t pid, int saved_stdin, int saved_stdout,
		t_shell *sh)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		restore_stdio(saved_stdin, saved_stdout);
		sh->error = 1;
		return (1);
	}
	restore_stdio(saved_stdin, saved_stdout);
	return (store_status(sh, status));
}

static int	execute_external(t_shell *sh, t_command *cmd, int saved_stdin,
		int saved_stdout)
{
	char	*path;
	pid_t	pid;

	path = resolve_path(sh, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		restore_stdio(saved_stdin, saved_stdout);
		sh->error = (char)127;
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		restore_stdio(saved_stdin, saved_stdout);
		sh->error = 1;
		return (1);
	}
	if (pid == 0)
	{
		execve(path, cmd->argv, sh->envp);
		perror(path);
		free(path);
		exit(127);
	}
	free(path);
	return (wait_and_restore(pid, saved_stdin, saved_stdout, sh));
}

int	execute_command(t_shell *sh, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!sh)
		return (1);
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		sh->error = 0;
		return (0);
	}
	if (apply_redirs(cmd, &saved_stdin, &saved_stdout))
	{
		sh->error = 1;
		return (1);
	}
	if (is_builtin(cmd))
	{
		run_builtin_parent(sh, cmd);
		restore_stdio(saved_stdin, saved_stdout);
		return ((sh->error != 0));
	}
	return (execute_external(sh, cmd, saved_stdin, saved_stdout));
}
