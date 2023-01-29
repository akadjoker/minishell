/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lupereir          #+#    #+#             */
/*   Updated: 2023/01/13 17:51:18 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(char **cmd, int i)
{
	while (cmd && cmd[i])
	{
		ft_printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			ft_printf(" ");
	}
}

int	echo(char **cmd)
{
	int		has_n;
	int		i;
	int		ret;

	has_n = 0;
	i = 1;
	if (cmd[i] != NULL)
	{
		ret = ft_strcmp(cmd[i], "-n");
		while (ret == FALSE)
		{
			has_n = 1;
			i++;
			if (cmd[i] == NULL)
				break ;
			ret = ft_strcmp(cmd[i], "-n");
		}
	}
	print_echo(cmd, i);
	if (has_n == FALSE)
		ft_printf("\n");
	g_shell.noerr = 0;
	return (1);
}

/*
* function for the export 
*/
void	error_export(char **cmd, int i)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_shell.noerr = EPERM;
}
