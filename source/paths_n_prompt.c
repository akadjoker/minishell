/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_n_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 18:28:44 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path_str(void)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (!ft_strcmp(g_shell.env->item[c]->key, "PATH"))
			return (g_shell.env->item[c]->value);
		c++;
	}
	return ("");
}

char	**get_paths(void)
{
	char	*paths;
	char	**ret;

	paths = get_path_str();
	ret = ft_split(paths, ':');
	return (ret);
}

/*
minishell ou a path?? no proppt?
*/
char	*get_prompt(void)
{
	char	cwd[2048];
	char	*prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	if (prompt == NULL)
	{
		perror("Error: ");
		free_and_exit();
	}
	return (prompt);
}

int	is_path(char **cmd, char **n_env)
{
	int	c;

	c = 0;
	if (cmd[0][0] == '/')
	{
		return (1);
	}
	while (cmd[0][c])
	{
		if (cmd[0][c] == '/')
		{
			if (cmd[0][c] + 1 == '\0')
				execve(cmd[0], cmd, n_env);
		}
		c++;
	}
	return (0);
}

void	free_and_exit(void)
{
	free_tables(g_shell.env);
	free_tables(g_shell.local);
	exit(g_shell.noerr);
}
