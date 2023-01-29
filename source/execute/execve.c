/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/13 17:13:21 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_executable(char *new_path)
{
	struct stat	buffer;

	if (stat(new_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char	**create_command_for_exec(char **cmd, char **paths)
{
	char	*new_path;
	char	**new_cmd;
	int		c;

	c = 0;
	new_cmd = (char **)malloc(sizeof(char **));
	if (is_executable(cmd[0]))
		new_cmd[0] = ft_strdup(cmd[0]);
	else
	{
		while (paths[c])
		{
			new_path = ft_strjoin(paths[c], "/");
			new_cmd[0] = ft_strjoin(new_path, cmd[0]);
			free(new_path);
			if (is_executable(new_cmd[0]))
				break ;
			free(new_cmd[0]);
			c++;
		}
	}
	return (new_cmd);
}

void	do_exec(char **cmd, char **n_env)
{
	int			status;
	char		**paths;
	pid_t		pid;
	char		**new_cmd;

	paths = get_paths();
	new_cmd = NULL;
	define_signals_exec();
	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		free_and_exit();
	}
	else if (pid == 0)
	{
		new_cmd = create_command_for_exec(cmd, paths);
		final_exec(new_cmd, cmd, n_env);
	}
	waitpid(pid, &status, 0);
	g_shell.noerr = WEXITSTATUS(status);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}
