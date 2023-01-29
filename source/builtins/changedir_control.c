/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lupereir          #+#    #+#             */
/*   Updated: 2023/01/13 17:51:11 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	control_cd_minus(char *tmp)
{
	char	*old;

	old = search_array_by_key("OLDPWD");
	if (old)
	{
		ft_printf("%s\n", old);
		chdir(old);
		g_shell.noerr = 0;
	}
	else
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		free(tmp);
		g_shell.noerr = EPERM;
	}
}

void	control_cd_minus_two(char **cmd, char *slash, char *home)
{
	if (ft_strncmp(cmd[1], "~-", 5) == 0)
		chdir(search_array_by_key("OLDPWD"));
	else if (ft_strncmp(cmd[1], "~", 4) == 0
		|| ft_strncmp(cmd[1], "--", 4) == 0)
		chdir(home);
	else if (ft_strncmp(cmd[1], "/", 4) == 0)
		chdir(slash);
	else
		chdir(cmd[1]);
}

void	cd_error_file(char **cmd)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
