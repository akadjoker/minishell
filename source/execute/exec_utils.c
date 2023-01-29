/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/13 18:42:30 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_integer(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
error from execve
*/
void	execve_error(char *cmd)
{
	ft_putstr_fd("*Minishell: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': ", 2);
	g_shell.noerr = errno;
	ft_putstr_fd(strerror(g_shell.noerr), 2);
	ft_putstr_fd("\n", 2);
	exit(g_shell.noerr);
}

void	final_exec(char **new_cmd, char **cmd, char **n_env)
{
	if (!new_cmd)
	{
		ft_putendl_fd("Command not found", 2);
		exit(g_shell.noerr);
		return ;
	}
	if (execve(new_cmd[0], cmd, n_env) == -1)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("': ", 2);
		ft_putendl_fd("command not found", 2);
		g_shell.noerr = 127;
		exit(g_shell.noerr);
	}
	g_shell.noerr = errno;
	exit(g_shell.noerr);
}
