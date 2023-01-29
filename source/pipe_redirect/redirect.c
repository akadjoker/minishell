/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 07:53:26 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redirect_out(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag, 0777);
	if (file_fd == -1)
	{
		ft_putendl_fd("Error: bad file decriptor", 2);
	}
	else
	{
		dup2(file_fd, STDOUT);
		close(file_fd);
	}
}

static void	redirect_in(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag);
	if (file_fd == -1)
	{
		ft_putendl_fd("Error: bad file decriptor", 2);
	}
	else
		dup2(file_fd, STDIN);
}

void	build_redirect(char *redirect, char *file, int *save_fd)
{
	if (!(ft_strcmp(redirect, ">")))
		redirect_out(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!(ft_strcmp(redirect, ">>")))
		redirect_out(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!(ft_strcmp(redirect, "<")))
		redirect_in(file, O_RDONLY | O_CREAT);
	else if (!(ft_strcmp(redirect, "<<")))
		execute_heredoc(file, save_fd);
}

int	is_redirect(char *cmd)
{
	if (!(ft_strcmp(cmd, ">")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, ">>")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, "<")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, "<<")))
		return (TRUE);
	return (FALSE);
}
