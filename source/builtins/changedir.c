/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:23:29 by lupereir          #+#    #+#             */
/*   Updated: 2023/01/13 17:51:44 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_args(char **cmd, int i)
{
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_shell.noerr = EPERM;
	}
	return (i);
}

static void	cd_home(t_cd *cd_list)
{
	if (cd_list->i == 1)
	{
		insert_or_modify_by_key("OLDPWD", cd_list->tmp);
		chdir(cd_list->home);
	}
}

static void	cd_init(t_cd *cd_list, char **cmd)
{
	cd_list->i = cd_args(cmd, 1);
	cd_list->tmp = NULL;
	cd_list->home = search_array_by_key("HOME");
	cd_list->slash = "/";
	g_shell.noerr = 0;
}

int	cd(char **cmd)
{
	t_cd	cd_list;
	char	buffer[2048];

	cd_init(&cd_list, cmd);
	if (g_shell.noerr == EPERM)
		return (g_shell.noerr);
	cd_list.tmp = getcwd(cd_list.tmp, 0);
	cd_home(&cd_list);
	if (cd_list.i == 2)
	{
		if (ft_strncmp(cmd[1], "-", 4) == 0)
		{
			control_cd_minus(cd_list.tmp);
			if (g_shell.noerr == EPERM)
				return (g_shell.noerr);
		}
		else
			control_cd_minus_two(cmd, cd_list.slash, cd_list.home);
		insert_or_modify_by_key("OLDPWD", cd_list.tmp);
		if (g_shell.noerr == ENOENT)
			cd_error_file(cmd);
	}
	free(cd_list.tmp);
	insert_or_modify_by_key("PWD", getcwd(buffer, 2048));
	return (g_shell.noerr);
}
