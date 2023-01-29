/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:03:21 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 07:35:24 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interrupt(int signal)
{
	g_shell.noerr = 128 + signal;
	ft_printf("*interrupt\n");
}

/*
CTRL + C
*/
void	prompt_handler(int signal)
{
	if (isatty(STDIN))
	{
		g_shell.noerr = 128 + signal;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	define_signals(void)
{
	signal(SIGINT, prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
CTLD + D exit
*/
static void	exec_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_shell.noerr = 130;
		ft_printf("\n");
	}
	if (signal == SIGQUIT)
	{
		g_shell.noerr = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	define_signals_exec(void)
{
	signal(SIGINT, exec_handler);
	signal(SIGQUIT, exec_handler);
}
