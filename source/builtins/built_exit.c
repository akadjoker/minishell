/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:23:29 by lupereir          #+#    #+#             */
/*   Updated: 2023/01/07 07:39:02 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_terminal(char **cmd, char	**n_env, char **old_cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		while (ft_isdigit(cmd[1][i]))
			i++;
		if (cmd[1][i] == '\0' && !cmd[2])
			g_shell.noerr = ft_atoi(cmd[1]);
		else if (cmd[2])
			g_shell.noerr = EPERM;
		else if (!cmd[2] && cmd[1][i] != '\0')
			g_shell.noerr = ENOENT;
	}
	else
		g_shell.noerr = 0;
	ft_free_split(cmd);
	ft_free_split(old_cmd);
	ft_free_split(n_env);
	free_and_exit();
}
